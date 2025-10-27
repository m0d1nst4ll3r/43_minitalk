/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:20:27 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:20:38 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_response = 0;

static void	sigusr_handler(int signum)
{
	(void)signum;
	g_response = 1;
}

int	main(int ac, char **av)
{
	struct sigaction	act;
	sigset_t			set;
	int					server;

	if (ac != 3)
		return (0);
	if (init_set(&set) || init_act(&act, set, sigusr_handler))
		return (1);
	server = ft_atoi(av[1]);
	if (server <= 0)
		return (0);
	send_pid_repeat(server);
	send_msg(server, av[2]);
	if (VERBOSE)
		printf(C_SUCCESS);
	return (0);
}
