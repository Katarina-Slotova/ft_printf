/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_to_power_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:17:31 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:30:46 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_x_to_power_n(int precision)
{
	int	i;
	int	number;

	number = 1;
	i = 0;
	while (i < precision)
	{
		number *= 10;
		i++;
	}
	return (number);
}
