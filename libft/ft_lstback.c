/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:59:43 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/07 13:42:49 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstback(t_list **begin_list, void *data)
{
	t_list	*head;
	t_list	*current;
	t_list	*ptr;

	head = *begin_list;
	ptr = head;
	current = 0;
	if (head == 0)
		head = ft_create_node(data);
	else
	{
		current = ft_create_node(data);
		current->content = data;
		current->content_size = 0;
		current->next = 0;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = current;
	}
}
