/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:21:37 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/28 16:42:32 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int num)
{
	int	len;

	len = 0;
	if (num <= 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_length(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len--] = '\0';
	if (n == 0)
		return (ft_strcpy(str, "0"));
	if (n == -2147483648)
		return (ft_strcpy(str, "-2147483648"));
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		str[len] = '0' + (n % 10);
		n = n / 10;
		len--;
	}
	return (str);
}
