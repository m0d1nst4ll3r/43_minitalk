/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:32:06 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:26:26 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define C_PID_TIMEOUT	"Could not send PID to server :(\n"
# define C_MSG_TIMEOUT	"Could not send full message to server :(\n"
# define C_SUCCESS		"Message successfully sent to server ^-^\n"

# include "minitalk.h"

extern int	g_response;

// client_error.c
void	c_pid_timeout(void);
void	c_msg_timeout(void);

// client_send.c
void	send_pid_repeat(int server);
void	send_msg(int server, char *msg);

#endif
