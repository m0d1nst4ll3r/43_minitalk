/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:16:07 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 17:14:22 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	s_msg_timeout(void)
{
	if (VERBOSE)
		ft_printf(S_MSG_TIMEOUT);
}

void	s_pid_timeout(void)
{
	if (DEBUG)
		ft_printf(S_PID_TIMEOUT);
}
