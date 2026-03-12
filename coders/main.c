/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaudich <egaudich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:43 by egaudich          #+#    #+#             */
/*   Updated: 2026/03/12 14:54:43 by egaudich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_global	sim;

	if (check_args(argc, argv))
		return (1);
	init_sim(&sim, argv);
	return (0);
}
