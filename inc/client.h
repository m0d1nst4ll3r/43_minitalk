/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:32:06 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/01 16:03:07 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define C_SUCCESS		"Message successfully sent to server ^-^\n"
# define ERR_CPID		"No response after sending PID"
# define ERR_CSTART		"Lost server during first handshake"
# define ERR_CLEN		"Lost server while sending length"
# define ERR_CMSG		"Lost server while sending message"
# define ERR_CEARLY		"Server received extra bits"
# define ERR_CLATE		"Server expects too many bits"
# define ERR_CEND		"Lost server during last handshake"

# include "minitalk.h"

extern int	g_response;

// client_send.c
int		send_pid_repeat(int server);
int		send_msg(int server, char *msg);
int		send_byte(int server, char byte);
int		send_msg_len(int server, int msg_len);

#endif
