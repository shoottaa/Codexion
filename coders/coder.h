/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:02:27 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 20:02:27 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "types.h"
# include "log.h"
# include "dongle.h"
# include <unistd.h>

int		is_sim_active(t_global *sim);
void	*coder_routine(void *arg);
void	init_coders(t_global *sim);

#endif