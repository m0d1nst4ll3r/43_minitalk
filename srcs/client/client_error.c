/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:34:15 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 15:11:45 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	c_pid_timeout(void)
{
	if (VERBOSE)
		printf(C_PID_TIMEOUT);
	exit(1);
}

void	c_msg_timeout(void)
{
	if (VERBOSE)
		printf(C_MSG_TIMEOUT);
	exit(2);
}
