/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:20:27 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/29 18:38:13 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_response = 0;

static void	sigusr_handler(int signum)
{
	if (signum == S_PING)
		g_response = 1;
	else if (signum == S_END)
		g_response = 2;
}

static int	receive_end_signal(void)
{
	int	attempts;

	attempts = 0;
	while (attempts < MAX_TRIES)
	{
		if (!g_response)
			usleep(MSG_WAIT);
		if (g_response == S_END)
			return (0);
		attempts++;
	}
	return (1);
}

/*	Program steps:
 *
 * 1. Try sending pid to server
 *		- Try MAX_TRIES times at most
 *		- Wait PID_WAIT microseconds between bits and between tries
 *		- Server should ping to respond, if not, error out
 * 2. Send a handshake byte
 *		- From now on, and for subsequent steps:
 *			- Wait MSG_WAIT microseconds between bits
 *			- Server will ping after each bit unless an error occured
 *		- The handshake byte is defined in HANDSHAKE
 *		- This unique byte serves to avoid transmission errors
 *			- E.g multiple clients sending jumbled bits to the server
 * 3. Send message length as an int
 *		- This avoids further miscommunication errors
 * 4. Send message
 *		- Server will send special signal after having received enough bytes
 *			- If server sends early, it received too many bits by error
 *			- If server sends late, it skipped some bits
 *			- In both cases, error out
 * 5. Send last handshake byte
 *		- This is to help server confirm that everything is ok
*/
void	minitalk_client(char *msg, size_t msg_len, int server)
{
	if (send_pid_repeat(server))
		error(ERR_CPID);
	if (send_byte(server, HANDSHAKE))
		error(ERR_CSTART);
	if (send_msg_len(server, msg_len))
		error(ERR_CLEN);
	ret = send_msg(server, av[2]);
	if (ret == 1)
		error(ERR_CMSG);
	else if (ret == 2)
		error(ERR_CEARLY);
	if (receive_end_signal())
		error(ERR_CLATE);
	if (send_byte(server, HANDSHAKE))
		error(ERR_SEND);
}

int	main(int ac, char **av)
{
	struct sigaction	act;
	sigset_t			set;
	int					server;
	int					ret;

	if (ac != 3)
		return (0);
	if (init_set(&set) || init_act(&act, set, sigusr_handler))
		return (1);
	server = ft_atoi(av[1]);
	if (server <= 0)
		return (0);
	minitalk_client(av[2], ft_strlen(av[2]), server);
	if (VERBOSE)
		ft_printf(C_SUCCESS);
	return (0);
}
