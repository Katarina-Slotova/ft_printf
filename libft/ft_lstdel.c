/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 09:25:35 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/01 10:49:23 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next_link;
	t_list	*ptr;

	ptr = *alst;
	while (ptr)
	{
		next_link = ptr->next;
		del(ptr->content, ptr->content_size);
		free(ptr);
		ptr = next_link;
	}
	*alst = NULL;
}
