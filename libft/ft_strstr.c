/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:32:26 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/30 16:53:33 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	a;
	int	b;

	a = 0;
	if (needle[0] == '\0')
		return ((char *)&haystack[a]);
	while (haystack[a] != '\0')
	{
		b = 0;
		while (haystack[a + b] == needle[b])
		{
			b++;
			if (needle[b] == '\0')
				return ((char *)&haystack[a]);
		}
		a++;
	}
	return (0);
}
