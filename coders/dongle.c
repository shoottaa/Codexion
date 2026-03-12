/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:19:47 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 15:19:47 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"

int	init_dongles(t_global *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.num_coders)
	{
		sim->dongles[i].is_used = 0;
		sim->dongles[i].cooldown = 0;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
		sim->dongles[i].waiters = pqueue_create(sim->args.num_coders);
		i++;
	}
	return (0);
}

int	destroy_dongles(t_global *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.num_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		pqueue_destroy(sim->dongles[i].waiters);
		i++;
	}
	free(sim->dongles);
	return (0);
}
