/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_receive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:09:33 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:51:06 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	receive_byte(int client, char *byte)
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
			kill(client, S_RESPONSE);
		}
		else
			if (++attempts >= MAX_TRIES)
				return (1);
	}
	return (0);
}

int	receive_msg(int client, t_buf **list)
{
	char	byte;
	int		i;
	t_buf	*current;

	while (1)
	{
		current = lst_add_back(list);
		if (!current)
			return (1);
		i = 0;
		while (i < CHUNKSIZE)
		{
			if (receive_byte(client, &byte))
				return (1);
			current->buf[i] = byte;
			if (!byte)
				return (0);
			i++;
		}
		current->buf[i] = 0;
	}
}

int	receive_pid(void)
{
	int	i;
	int	pid;

	i = 31;
	pid = 0;
	while (1)
	{
		pid += g_bit << i;
		i--;
		g_bit = -1;
		if (i < 0)
			return (pid);
		if (g_bit < 0)
			usleep(PID_WAIT * 1.5);
		if (g_bit < 0)
			return (0);
	}
}
