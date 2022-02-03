/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 09:26:25 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/19 09:26:25 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	fresh = malloc(sizeof(t_list));
	if (!fresh)
		return (NULL);
	if (!content)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
		fresh->next = NULL;
	}
	else
	{
		fresh->content = malloc(sizeof(t_list) * content_size);
		if (!(fresh->content))
		{
			free(fresh);
			return (NULL);
		}
		ft_memcpy(fresh->content, content, content_size);
		fresh->content_size = content_size;
		fresh->next = NULL;
	}	
	return (fresh);
}
