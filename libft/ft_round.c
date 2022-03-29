/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:46:18 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:49:59 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_round(long double num, int precision)
{
	long double	rounded_num;
	long double	rounder;

	rounder = .5;
	while (precision > 0)
	{
		rounder = rounder / 10;
		precision--;
	}
	if (num >= 0)
		rounded_num = num + rounder;
	else
		rounded_num = num - rounder;
	return (rounded_num);
}
