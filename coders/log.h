/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:40:44 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 19:40:44 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# include "types.h"
# include <stdio.h>
# include <sys/time.h>

long	get_time_ms(void);
void	log_action(t_global *sim, int id, char *action);
void	log_burnout(t_global *sim, int id);

#endif