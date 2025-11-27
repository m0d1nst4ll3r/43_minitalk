/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:17:29 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:20:02 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	init_set(sigset_t *set)
{
	if (sigemptyset(set) || sigaddset(set, SIGUSR1) || sigaddset(set, SIGUSR2))
		return (1);
	return (0);
}

int	init_act(struct sigaction *act, sigset_t set, void (*f)(int))
{
	act->sa_handler = f;
	act->sa_flags = 0;
	act->sa_mask = set;
	if (sigaction(SIGUSR1, act, NULL) || sigaction(SIGUSR2, act, NULL))
		return (1);
	return (0);
}
