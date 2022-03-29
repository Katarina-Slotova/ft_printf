/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcharjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:02:33 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:04:12 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcharjoin(char *old_str, char c)
{
	char	*new_str;
	int		i;

	new_str = ft_strnew(ft_strlen(old_str) + 2);
	i = ft_strlen(new_str);
	ft_bzero(new_str, i);
	new_str = ft_strcpy(new_str, old_str);
	new_str[i] = c;
	return (new_str);
}
