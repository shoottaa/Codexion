/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:19:41 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 13:19:41 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

# include <unistd.h>

char	*ft_putstr_err(char *str);
int		is_not_valid_args(int argc, char **argv);
int		check_args(int argc, char **argv);

#endif