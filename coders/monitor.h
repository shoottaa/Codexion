/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:10:11 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/13 10:10:11 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "types.h"
# include "log.h"
# include "coder.h"
# include <unistd.h>

void	check_compile(t_global *sim);
void	check_burnout(t_global *sim);
void	*monitor_routine(void *arg);

#endif