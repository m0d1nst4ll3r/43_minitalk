/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:31:49 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/29 17:09:20 by rapohlen         ###   ########.fr       */
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

int	send_pid_repeat(int server)
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
		return (1);
	return (0);
}

int	send_byte(int server, char byte)
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
		if (g_response == 1)
		{
			g_response = 0;
			attempts = 0;
			i--;
		}
		else if (g_response == 2)
			return (2);
		else
			if (++attempts >= MAX_TRIES)
				return (1);
	}
	return (0);
}

int	send_msg(int server, char *msg)
{
	int	i;
	int	ret;

	i = 0;
	while (1)
	{
		ret = send_byte(server, msg[i]);
		if (ret)
			return (ret);
		if (!msg[i])
			break ;
		i++;
	}
	return (0);
}
