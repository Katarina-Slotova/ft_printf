/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:56:23 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/08 08:59:37 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*str1;
	unsigned char	*str2;

	index = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[index] != '\0' && str2[index] != '\0' && index < n)
	{
		if (str1[index] != str2[index])
			return (str1[index] - str2[index]);
		index++;
	}
	if ((str1[index] == '\0' && str2[index] == '\0') || index == n)
		return (0);
	else if (str1[index] == '\0')
		return (-str2[index]);
	else
		return (str1[index]);
}
