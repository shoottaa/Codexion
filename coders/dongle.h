/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:19:35 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 15:19:35 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "types.h"
# include <stdlib.h>

int	init_dongles(t_global *sim);
int	destroy_dongles(t_global *sim);

#endif