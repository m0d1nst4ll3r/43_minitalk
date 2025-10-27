/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:16:07 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 15:33:33 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	s_msg_timeout(void)
{
	if (VERBOSE)
		printf(S_MSG_TIMEOUT);
}

void	s_pid_timeout(void)
{
	if (DEBUG)
		printf(S_PID_TIMEOUT);
}
