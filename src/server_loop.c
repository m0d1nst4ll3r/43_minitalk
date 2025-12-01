/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:23:39 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/01 20:27:55 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	error(char *err)
{
	if (VERBOSE_ERR)
		ft_fprintf(2, "%s\n", err);
}

static void	loop_step_2(int client, int msg_len)
{
	char	byte;
	char	*msg;
	int		ret;

	ret = receive_msg(client, &msg, msg_len);
	if (ret == 1)
		error(ERR_SMALLOC);
	else if (ret == 2)
		error(ERR_SMSG);
	else if (receive_byte(client, &byte))
		error(ERR_SNOEND);
	else if (byte != (char)HANDSHAKE)
		error(ERR_SBADEND);
	else
		print_msg(msg, client);
	free(msg);
}

static void	loop_step_1(int client)
{
	int		msg_len;
	char	byte;

	kill(client, S_PING);
	if (receive_byte(client, &byte))
		error(ERR_SNOSTART);
	else if (byte != (char)HANDSHAKE)
		error(ERR_SBADSTART);
	else if (receive_msg_len(client, &msg_len))
		error(ERR_SNOLEN);
	else if (msg_len < 0)
		error(ERR_SBADLEN);
	else
		loop_step_2(client, msg_len);
}

/*	Program steps:
 *
 * 0. Run an infinite loop where we pause and wait for any signal.
 * 1. The first signal is interpreted as the first bit of a pid
 *		- The next MAX_PID_BITS - 1 bits are interpreted as the following bits
 *		- The resulting pid is inspected for obvious errors (<= 0, > MAX_PID)
 * 2. If the pid was correct, we send a response and wait for a handshake byte
 *		- At this point we start responding to every bit received with a ping
 * 3. If the handshake was correctly received, we wait for the 32-bits msg_len
 *		- This value represents how many bytes we will be expecting in the msg
 *		- We also inspect that value for obvious errors (< 0, empty msg is ok)
 * 4. If the msg_len was correctly received, we start receiving bytes
 *		- We stop at msg_len bytes received
 * 5. We send a special S_END signal to signify we are done
 * 6. We wait for a last handshake which should signify everything went well
 *
 * Communication takes significantly more time with all the pinging,
 *	handshakes, and msg_len, but this is done to avoid errors due to,
 *	for example, multiple clients being executed in parallel.
 */
void	server_loop(void)
{
	int		client;

	while (1)
	{
		if (g_bit < 0)
			pause();
		client = receive_pid();
		if (client == -1)
			error(ERR_SPIDINC);
		else if (client <= 0 || client > MAX_PID)
			error(ERR_SPID);
		else
			loop_step_1(client);
	}
}
