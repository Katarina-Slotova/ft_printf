/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:23:17 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/08 09:04:02 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	index;
	size_t	dest_len;

	index = 0;
	dest_len = ft_strlen(s1);
	while (s2[index] != '\0' && index < n)
	{
		s1[dest_len + index] = s2[index];
		index++;
	}
	s1[dest_len + index] = '\0';
	return (s1);
}
