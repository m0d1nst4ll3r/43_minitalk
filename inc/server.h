/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:34:58 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/29 18:39:58 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

# define CHUNKSIZE		1000
# define S_PING			SIGUSR1
# define S_END			SIGUSR2

typedef struct s_buf
{
	char			buf[CHUNKSIZE + 1];
	struct s_buf	*next;
}	t_buf;

extern int	g_bit;

// util_lst.c
t_buf	*lst_add_back(t_buf **lst);
void	lst_clear(t_buf **lst);
void	lst_print(t_buf *lst, int client);

// server_error.c
void	s_msg_timeout(void);
void	s_pid_timeout(void);

// server_receive.c
int		receive_pid(void);
int		receive_msg(int client, t_buf **list);

#endif
