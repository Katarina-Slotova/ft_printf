/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_s1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:05:22 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:07:10 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (s1 && s2)
	{
		if (ret != NULL)
		{
			i = 0;
			j = 0;
			while (s1[i])
			{
				ret[i] = s1[i];
				i++;
			}
			while (s2[j])
				ret[i++] = s2[j++];
			ret[i] = '\0';
			free(s1);
			return (ret);
		}
	}
	return (NULL);
}
