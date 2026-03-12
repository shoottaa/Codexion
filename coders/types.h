/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:44:25 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 13:44:25 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include "pqueue.h"

typedef struct s_args
{
	int	num_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_args;

typedef struct s_pqueue	t_pqueue;

typedef struct s_dongle
{
	int				is_used;
	long			cooldown;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_pqueue		*waiters;
}	t_dongle;

typedef struct s_global	t_global;

typedef struct s_coder
{
	int			id;
	pthread_t	thread;
	int			num_compile;
	long		last_compile_time;
	long		deadline;
	t_dongle	*dongle_left;
	t_dongle	*dongle_right;
	t_global	*global;
}	t_coder;

typedef struct s_global
{
	t_args			args;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	mutex_flag;
	int				flag;
	pthread_mutex_t	mutex_logging;
	long			start_timestamp;
}	t_global;

#endif