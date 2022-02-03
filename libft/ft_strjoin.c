/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:08:59 by kslotova          #+#    #+#             */
/*   Updated: 2022/01/03 11:20:57 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(const char *s1, const char *s2, char *new_str,
	int str1_len)
{
	int	i;

	i = 0;
	if (!new_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new_str[str1_len + i] = s2[i];
		i++;
	}
	new_str[str1_len + i] = '\0';
	return (new_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		str1_len;
	int		str2_len;
	int		i;
	char	*new_str;

	if (!s1 || !s2)
		return (0);
	str1_len = ft_strlen(s1);
	str2_len = ft_strlen(s2);
	i = 0;
	new_str = (char *)malloc(sizeof(char) * (str1_len + str2_len + 1));
	new_str = ft_join(s1, s2, new_str, str1_len);
	return (new_str);
}
