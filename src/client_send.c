/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:31:49 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:29:25 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_pid(int server, int client)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		if ((client >> i) & 1)
			kill(server, BIT_1);
		else
			kill(server, BIT_0);
		usleep(PID_WAIT);
		i--;
	}
}

void	send_pid_repeat(int server)
{
	int	client;
	int	attempts;

	client = getpid();
	attempts = 0;
	while (attempts < MAX_TRIES)
	{
		send_pid(server, client);
		if (!g_response)
			usleep(PID_WAIT);
		if (g_response)
		{
			g_response = 0;
			break ;
		}
		attempts++;
	}
	if (attempts >= MAX_TRIES)
		c_pid_timeout();
}

static void	send_byte(int server, char byte)
{
	int	i;
	int	attempts;

	i = 7;
	attempts = 0;
	while (i >= 0)
	{
		if ((byte >> i) & 1)
			kill(server, BIT_1);
		else
			kill(server, BIT_0);
		if (!g_response)
			usleep(MSG_WAIT);
		if (g_response)
		{
			g_response = 0;
			attempts = 0;
			i--;
		}
		else
			if (++attempts >= MAX_TRIES)
				c_msg_timeout();
	}
}

void	send_msg(int server, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		send_byte(server, msg[i]);
		i++;
	}
	send_byte(server, 0);
}
