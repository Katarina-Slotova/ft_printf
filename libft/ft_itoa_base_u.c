/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:28:22 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:28:44 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_u(unsigned long long int num, int base)
{
	char	*str;
	int		i;

	if (base < 2 || base > 16)
		return (NULL);
	i = ft_numlen_base_u(num, base);
	str = ft_strnew(i);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (i >= 0 && str[i] != '-')
	{
		str[i] = ft_base_u(num, base);
		num = num / base;
		i--;
	}
	return (str);
}
