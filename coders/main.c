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

#include <signal.h>
#include "main.h"

static void	handle_sigint(int sig)
{
	static t_global	*g_sim = NULL;

	(void)sig;
	if (g_sim)
		g_sim->flag = 1;
}

int	main(int argc, char **argv)
{
	t_global			sim;
	struct sigaction	sa;

	if (check_args(argc, argv))
		return (1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	init_sim(&sim, argv);
	return (0);
}
