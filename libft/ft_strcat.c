/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:50:16 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/08 09:00:25 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	index;
	int	dest_len;

	index = 0;
	dest_len = ft_strlen(s1);
	while (s2[index] != '\0')
	{
		s1[dest_len + index] = s2[index];
		index++;
	}
	s1[dest_len + index] = '\0';
	return (s1);
}
