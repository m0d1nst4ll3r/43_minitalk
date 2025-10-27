/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:21:01 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:30:40 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	g_bit = -1;

static void	sigusr_handler(int signum)
{
	if (signum == BIT_0)
		g_bit = 0;
	else
		g_bit = 1;
}

void	server_loop(void)
{
	int		client;
	t_buf	*lst;

	lst = NULL;
	while (1)
	{
		if (g_bit < 0)
			pause();
		client = receive_pid();
		if (client)
		{
			kill(client, S_RESPONSE);
			if (!receive_msg(client, &lst))
				lst_print(lst, client);
			else
				s_msg_timeout();
			lst_clear(&lst);
		}
		else
			s_pid_timeout();
	}
}

int	main(void)
{
	struct sigaction	act;
	sigset_t			set;

	print_pid();
	if (init_set(&set) || init_act(&act, set, sigusr_handler))
		return (1);
	server_loop();
	return (0);
}
