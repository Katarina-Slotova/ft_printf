/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:57:31 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/30 11:41:55 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*new_str;

	i = 0;
	if (!s || !f)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (0);
	while (s[i] != '\0')
	{
		new_str[i] = (f)(s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
