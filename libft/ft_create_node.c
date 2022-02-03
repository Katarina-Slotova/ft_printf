/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:45:16 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/20 11:12:31 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_node(void *content)
{
	t_list	*new_node;

	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
