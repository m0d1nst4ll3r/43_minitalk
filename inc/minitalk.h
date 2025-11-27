/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:11:22 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:12:50 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef VERBOSE
#  define VERBOSE		1
# endif

# ifndef DEBUG
#  define DEBUG			0
# endif

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

// TODO REPLACE PRINTF WITH OWN
# include <stdio.h>

// util.c
void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(long n);
void	print_pid(void);
int		ft_atoi(char *s);

// util_sig.c
int		init_set(sigset_t *set);
int		init_act(struct sigaction *act, sigset_t set, void (*f)(int));

#endif
