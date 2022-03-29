/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:44:22 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:44:42 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long int num, int base)
{
	char	*str;
	int		i;

	if (base < 2 || base > 16)
		return (NULL);
	i = ft_numlen_base(num, base);
	str = ft_strnew(i);
	if (!str)
		return (NULL);
	if (num < 0)
		str[0] = '-';
	str[i--] = '\0';
	while (i >= 0 && str[i] != '-')
	{
		str[i] = ft_base(num, base);
		num = num / base;
		i--;
	}
	return (str);
}
