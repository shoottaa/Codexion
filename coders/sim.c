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

int	init_sim(t_global *sim, char **argv)
{
	sim->args.num_coders = atoi(argv[1]);
	sim->args.time_to_burnout = atoi(argv[2]);
	sim->args.time_to_compile = atoi(argv[3]);
	sim->args.time_to_debug = atoi(argv[4]);
	sim->args.time_to_refactor = atoi(argv[5]);
	sim->args.number_of_compiles_required = atoi(argv[6]);
	sim->args.dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		sim->args.scheduler = 0;
	else
		sim->args.scheduler = 1;
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
