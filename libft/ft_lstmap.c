/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 09:26:15 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/19 09:26:15 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*current;
	t_list	*temp;

	head = NULL;
	while (lst)
	{
		temp = (f)(lst);
		temp = ft_lstnew(temp->content, temp->content_size);
		if (!head)
		{
			head = temp;
			current = temp;
		}
		if (!temp)
		{
			free(temp);
			return (NULL);
		}
		current->next = temp;
		current = current->next;
		lst = lst->next;
	}
	return (head);
}
