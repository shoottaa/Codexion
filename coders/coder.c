/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:02:44 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 20:02:44 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

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

void	*coder_routine(void *arg)
{
	t_coder		*coder;
	t_global	*sim;

	coder = (t_coder *)arg;
	sim = coder->global;
	coder->deadline = get_time_ms() + sim->args.time_to_burnout;
	while (is_sim_active(sim))
	{
		take_dongles(coder);
		coder->deadline = get_time_ms() + sim->args.time_to_burnout;
		log_action(sim, coder->id, "is compiling");
		usleep(sim->args.time_to_compile * 1000);
		release_dongles(coder);
		log_action(sim, coder->id, "is debugging");
		usleep(sim->args.time_to_debug * 1000);
		log_action(sim, coder->id, "is refactoring");
		usleep(sim->args.time_to_refactor * 1000);
		coder->num_compile++;
	}
	return (NULL);
}

void	init_coders(t_global *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.num_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].num_compile = 0;
		sim->coders[i].last_compile_time = 0;
		sim->coders[i].deadline = get_time_ms() + sim->args.time_to_burnout;
		sim->coders[i].dongle_left = &sim->dongles[i];
		sim->coders[i].dongle_right = &sim->dongles[(i + 1)
			% sim->args.num_coders];
		sim->coders[i].global = sim;
		pthread_create(&sim->coders[i].thread, NULL,
			coder_routine, &sim->coders[i]);
		i++;
	}
}
