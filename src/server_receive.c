/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_receive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:09:33 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/01 20:01:44 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	receive_byte(int client, char *byte)
{
	int		i;
	int		attempts;

	*byte = 0;
	attempts = 0;
	i = 7;
	while (i >= 0)
	{
		if (g_bit < 0)
			usleep(MSG_WAIT * 1.5);
		if (g_bit >= 0)
		{
			*byte += g_bit << i;
			g_bit = -1;
			i--;
			attempts = 0;
			kill(client, S_PING);
		}
		else if (++attempts >= MAX_TRIES)
			return (1);
	}
	return (0);
}

static void	send_end_signal(int client)
{
	int	attempts;

	attempts = 0;
	while (g_bit < 0 && attempts++ < MAX_TRIES)
	{
		kill(client, S_END);
		if (g_bit < 0)
			usleep(MSG_WAIT * 1.5);
		attempts++;
	}
}

int	receive_msg(int client, char **msg, int msg_len)
{
	char	byte;
	int		i;

	i = 0;
	*msg = malloc(msg_len + 1);
	if (!*msg)
		return (1);
	while (i < msg_len)
	{
		if (receive_byte(client, &byte))
			return (2);
		msg[0][i] = byte;
		i++;
	}
	msg[0][i] = 0;
	send_end_signal(client);
	return (0);
}

int	receive_pid(void)
{
	int	i;
	int	pid;

	i = MAX_PID_BITS - 1;
	pid = 0;
	while (1)
	{
		pid += g_bit << i;
		i--;
		g_bit = -1;
		if (i < 0)
			break ;
		if (g_bit < 0)
			usleep(PID_WAIT * 1.5);
		if (g_bit < 0)
			return (-1);
	}
	return (pid);
}

int	receive_msg_len(int client, int *msg_len)
{
	int	i;
	int	attempts;

	i = 31;
	*msg_len = 0;
	while (i >= 0)
	{
		if (g_bit < 0)
			usleep(MSG_WAIT * 1.5);
		if (g_bit >= 0)
		{
			*msg_len += g_bit << i;
			g_bit = -1;
			i--;
			attempts = 0;
			kill(client, S_PING);
		}
		else if (++attempts >= MAX_TRIES)
			return (1);
	}
	return (0);
}
