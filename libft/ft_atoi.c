/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:05:57 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/03 09:05:57 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	index;
	int	sign;

	sign = 1;
	index = 0;
	result = 0;
	while (str[index] != '\0')
	{
		while (str[index] == ' ' || str[index] == '\v' || str[index] == '\t'
			|| str[index] == '\r' || str[index] == '\n' || str[index] == '\f')
			index++;
		if (str[index] == '-')
			sign = -1;
		if (str[index] == '-' || str[index] == '+')
			index++;
		while (str[index] >= '0' && str[index] <= '9')
		{
			result = result * 10 + (str[index] - '0');
			index++;
		}
		if (str[index] <= '0' || str[index] >= '9')
			return (result * sign);
	}
	return (result * sign);
}
