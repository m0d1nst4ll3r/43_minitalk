/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:11:22 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/29 18:39:54 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef VERBOSE
#  define VERBOSE		1
# endif

# ifndef VERBOSE_ERR
#  define VERBOSE_ERR	1
# endif

# define ERR_CPID		"No response after sending PID"
# define ERR_CSTART		"Lost server during first handshake"
# define ERR_CLEN		"Lost server while sending length"
# define ERR_CMSG		"Lost server while sending message"
# define ERR_CEARLY		"Server missed bytes"
# define ERR_CLATE		"Server expects too many bytes"
# define ERR_CEND		"Lost server during last handshake"

# define ERR_SPID		"Received bad PID"
# define ERR_SPIDINC	"Received incomplete PID"
# define ERR_SSTART		"Lost client during first handshake"
# define ERR_SLEN		"Lost client while receiving length"
# define ERR_SMSG		"Lost client while receiving message"
# define ERR_SEARLY		"Client did not confirm full receipt"
# define ERR_SEND		"Lost client during last handshake"

# define HANDSHAKE		0xff

# define S_PING			SIGUSR1
# define S_END			SIGUSR2
# define BIT_0			SIGUSR1
# define BIT_1			SIGUSR2
// Max amount of tries for sending/receiving pid/msg bits before giving up
# define MAX_TRIES		10
// Delay for sending PID bits
// Lower value would be faster but would cause rare errors
# define PID_WAIT		250
// Delay for sending msg bits
// Since client sends after server response, this has little effect on speed
# define MSG_WAIT		500

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>

# include "libft.h"

// util.c
void	print_pid(void);

// util_sig.c
int		init_set(sigset_t *set);
int		init_act(struct sigaction *act, sigset_t set, void (*f)(int));

#endif
