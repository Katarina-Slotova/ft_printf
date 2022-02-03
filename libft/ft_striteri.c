/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:06:34 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/03 16:41:37 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int n, char *c))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		(f)(i, &s[i]);
		i++;
	}
}
