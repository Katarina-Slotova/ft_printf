/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:42:01 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/03 16:46:24 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		string_len;
	char	*new_str;

	i = 0;
	string_len = ft_strlen(s1);
	new_str = (char *)malloc(sizeof(char) * (string_len + 1));
	if (!new_str)
		return (0);
	while (i < string_len)
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
