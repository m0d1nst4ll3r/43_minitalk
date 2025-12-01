/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:34:58 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/01 20:23:23 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define ERR_SPID		"Received bad PID"
# define ERR_SPIDINC	"Received incomplete PID"
# define ERR_SNOSTART	"Lost client during first handshake"
# define ERR_SBADSTART	"Received bad handshake"
# define ERR_SNOLEN		"Lost client while receiving length"
# define ERR_SBADLEN	"Received bad length"
# define ERR_SMSG		"Lost client while receiving message"
# define ERR_SEARLY		"Client did not confirm full receipt"
# define ERR_SNOEND		"Lost client during last handshake"
# define ERR_SBADEND	"Received bad last handshake"
# define ERR_SMALLOC	"Malloc failed"

extern int	g_bit;

// server_loop.c
void	server_loop(void);

// server_receive.c
int		receive_pid(void);
int		receive_byte(int client, char *byte);
int		receive_msg(int client, char **msg, int msg_len);
int		receive_msg_len(int client, int *msg_len);

// server_print.c
void	print_pid(void);
void	print_msg(char *msg, int client);

#endif
