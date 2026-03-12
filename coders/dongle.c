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
#include <pthread.h>

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
		sim->dongles[i].waiters = pq_create(sim->args.num_coders);
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
		pq_destroy(sim->dongles[i].waiters);
		i++;
	}
	free(sim->dongles);
	return (0);
}

void	take_one_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	if (coder->global->args.scheduler == 1)
		pq_push(dongle->waiters, coder, coder->deadline);
	else
		pq_push(dongle->waiters, coder, get_time_ms());
	while (dongle->is_used || get_time_ms() < dongle->cooldown
		|| dongle->waiters->node[0].coder != coder)
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	pq_pop(dongle->waiters);
	dongle->is_used = 1;
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_dongles(t_coder *coder)
{
	t_dongle	*dongle;

	dongle = coder->dongle_left;
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_used = 0;
	dongle->cooldown = get_time_ms() + coder->global->args.dongle_cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
	dongle = coder->dongle_right;
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_used = 0;
	dongle->cooldown = get_time_ms() + coder->global->args.dongle_cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

void	take_dongles(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		take_one_dongle(coder, coder->dongle_left);
		log_action(coder->global, coder->id, "has taken a dongle");
		take_one_dongle(coder, coder->dongle_right);
		log_action(coder->global, coder->id, "has taken a dongle");
	}
	else
	{
		take_one_dongle(coder, coder->dongle_right);
		log_action(coder->global, coder->id, "has taken a dongle");
		take_one_dongle(coder, coder->dongle_left);
		log_action(coder->global, coder->id, "has taken a dongle");
	}
}
