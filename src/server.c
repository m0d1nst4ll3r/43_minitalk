/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:21:01 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/01 20:26:59 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	g_bit = -1;

static void	sigusr_handler(int signum)
{
	if (g_bit == -1)
	{
		if (signum == BIT_0)
			g_bit = 0;
		else
			g_bit = 1;
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
