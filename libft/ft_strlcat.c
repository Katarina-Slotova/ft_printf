/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 5021/11/04 09:11:50 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/29 18:03:09 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	while (dst[j])
		j++;
	if (j > dstsize)
		dest_len = dstsize;
	else
		dest_len = j;
	if (dstsize != 0)
	{
		while (src[i] && j < dstsize - 1)
			dst[j++] = src[i++];
	}		
	dst[j] = '\0';
	return (dest_len + src_len);
}
