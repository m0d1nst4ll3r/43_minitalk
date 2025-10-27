/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:53:36 by rapohlen          #+#    #+#             */
/*   Updated: 2025/10/22 16:30:48 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_buf	*lst_add_back(t_buf **lst)
{
	t_buf	*new;
	t_buf	*last;

	new = malloc(sizeof(t_buf));
	if (!new)
		return (new);
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last && last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

// Frees all and sets *lst to NULL
void	lst_clear(t_buf **lst)
{
	t_buf	*cur;
	t_buf	*last;

	cur = *lst;
	while (cur)
	{
		last = cur;
		cur = cur->next;
		free(last);
	}
	*lst = NULL;
}

void	lst_print(t_buf *lst, int client)
{
	if (VERBOSE)
		printf("Message from %d :\n", client);
	while (lst)
	{
		printf("%s", lst->buf);
		lst = lst->next;
	}
	printf("\n");
}
