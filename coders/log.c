/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:45:15 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 19:45:15 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	log_action(t_global *sim, int id, char *action)
{
	long	time;

	pthread_mutex_lock(&sim->mutex_flag);
	if (sim->flag)
	{
		pthread_mutex_unlock(&sim->mutex_flag);
		return ;
	}
	pthread_mutex_unlock(&sim->mutex_flag);
	time = get_time_ms() - sim->start_timestamp;
	pthread_mutex_lock(&sim->mutex_logging);
	printf("%ld %d %s\n", time, id, action);
	pthread_mutex_unlock(&sim->mutex_logging);
}

void	log_burnout(t_global *sim, int id)
{
	long	time;

	time = get_time_ms() - sim->start_timestamp;
	pthread_mutex_lock(&sim->mutex_logging);
	printf("%ld %d burned out\n", time, id);
	pthread_mutex_unlock(&sim->mutex_logging);
}
