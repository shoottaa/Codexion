/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:07:44 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 13:07:44 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

char	*ft_putstr_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (str);
}

int	is_not_valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc - 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!((argv[i][j] >= '0' && argv[i][j] <= '9')))
			{
				ft_putstr_err("Error: Arguments must be positive integers.\n");
				return (1);
			}
			j++;
		}
		if (j == 0)
		{
			ft_putstr_err("Error: Arguments cannot be empty.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 10)
	{
		ft_putstr_err("Error: Wrong number of arguments.\n");
		return (1);
	}
	if (is_not_valid_args(argc, argv))
		return (1);
	if (strcmp(argv[9], "fifo") != 0 && strcmp(argv[9], "edf") != 0)
	{
		ft_putstr_err("Error: Bad scheduler. Use 'fifo' or 'edf'.\n");
		return (1);
	}
	return (0);
}
