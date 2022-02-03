/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:13:22 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/29 09:44:59 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*destination;

	i = 0;
	source = (unsigned char *)src;
	destination = (unsigned char *)dst;
	while (i < n)
	{
		destination[i] = source[i];
		if (destination[i] == (unsigned char)c)
		{
			dst = dst + '\0';
			return (&dst[i + 1] + '\0');
		}			
		i++;
	}
	return (0);
}
