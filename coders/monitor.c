/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:10:08 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/13 10:10:08 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "monitor.h"

void	check_compile(t_global *sim)
{
	int i;

	i = 0;
	while (i < sim->args.num_coders)
	{
		if (sim->coders[i].num_compile < sim->args.number_of_compiles_required)
			return ;
		i++;
	}
	pthread_mutex_lock(&sim->mutex_flag);
	sim->flag = 1;
	pthread_mutex_unlock(&sim->mutex_flag);
}

void	check_burnout(t_global *sim)
{
	int i;

	i = 0;
	while (i < sim->args.num_coders)
	{
		if (get_time_ms() > sim->coders[i].deadline)
		{
			log_burnout(sim, sim->coders[i].id);
            pthread_mutex_lock(&sim->mutex_flag);
            sim->flag = 1;
			pthread_mutex_unlock(&sim->mutex_flag);
            return ;
		}
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_global	*sim;

	sim = (t_global *)arg;
	while (is_sim_active(sim))
	{
		check_burnout(sim);
		check_compile(sim);
		usleep(1000);
	}
	return (NULL);
}
