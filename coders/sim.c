/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:58:55 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 14:58:55 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "sim.h"

int	is_sim_active(t_global *sim)
{
	pthread_mutex_lock(&sim->mutex_flag);
	if (sim->flag == 0)
	{
		pthread_mutex_unlock(&sim->mutex_flag);
		return (1);
	}
	pthread_mutex_unlock(&sim->mutex_flag);
	return (0);
}

static int	alloc_sim(t_global *sim)
{
	sim->coders = malloc(sizeof(t_coder) * sim->args.num_coders);
	sim->dongles = malloc(sizeof(t_dongle) * sim->args.num_coders);
	if (!sim->coders || !sim->dongles)
	{
		free(sim->coders);
		free(sim->dongles);
		return (1);
	}
	return (0);
}

static void	cleanup_sim(t_global *sim)
{
	destroy_dongles(sim);
	free(sim->coders);
	pthread_mutex_destroy(&sim->mutex_flag);
	pthread_mutex_destroy(&sim->mutex_logging);
}

void	parse_args(t_args *args, char **argv)
{
	args->num_coders = atoi(argv[1]);
	args->time_to_burnout = atoi(argv[2]);
	args->time_to_compile = atoi(argv[3]);
	args->time_to_debug = atoi(argv[4]);
	args->time_to_refactor = atoi(argv[5]);
	args->number_of_compiles_required = atoi(argv[6]);
	args->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		args->scheduler = 0;
	else
		args->scheduler = 1;
}

int	init_sim(t_global *sim, char **argv)
{
	int	i;

	parse_args(&sim->args, argv);
	if (alloc_sim(sim))
		return (1);
	sim->flag = 0;
	pthread_mutex_init(&sim->mutex_flag, NULL);
	pthread_mutex_init(&sim->mutex_logging, NULL);
	sim->start_timestamp = get_time_ms();
	init_dongles(sim);
	init_coders(sim);
	pthread_create(&sim->monitor, NULL, monitor_routine, sim);
	i = 0;
	while (i < sim->args.num_coders)
		pthread_join(sim->coders[i++].thread, NULL);
	pthread_join(sim->monitor, NULL);
	cleanup_sim(sim);
	return (0);
}
