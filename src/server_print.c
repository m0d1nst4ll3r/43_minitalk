/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:18:30 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/01 12:18:48 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_pid(void)
{
	ft_printf("PID : %d\n", getpid());
}

void	print_msg(char *msg, int client)
{
	if (VERBOSE)
		ft_printf("Message received from : %d\n", client);
	ft_printf("%s\n", msg);
}
