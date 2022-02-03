/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:47:59 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/29 11:13:31 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*source;
	char	*destination;

	i = 0;
	source = (char *)src;
	destination = (char *)dst;
	if (source == NULL && destination == NULL)
		return (0);
	if (destination > source)
	{
		while (len-- > 0)
			destination[len] = source[len];
	}
	else
	{
		while (i < len)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dst);
}
