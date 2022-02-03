/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:20:58 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/07 13:42:44 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *begin_list)
{
	t_list	*head;
	int		a;

	head = begin_list;
	a = 1;
	while (head->next)
	{
		head = head->next;
		a++;
	}
	return (a);
}
