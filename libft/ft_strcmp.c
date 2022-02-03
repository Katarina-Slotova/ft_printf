/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:29:06 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/03 16:20:22 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			index;
	unsigned char	*str1;
	unsigned char	*str2;

	index = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[index] != '\0' && str2[index] != '\0')
	{
		if (str1[index] != str2[index])
			return (str1[index] - str2[index]);
		index++;
	}
	if (str1[index] == '\0' && str2[index] == '\0')
		return (0);
	else if (str1[index] == '\0')
		return (-str2[index]);
	else
		return (str1[index]);
}
