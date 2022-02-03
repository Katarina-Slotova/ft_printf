/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:39:21 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/30 11:48:40 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int n, char c))
{
	unsigned int	i;
	char			*new_str;

	i = 0;
	if (!s || !f)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (0);
	while (s[i] != '\0')
	{
		new_str[i] = (f)(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
