/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:23:14 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 17:23:30 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_negative(double check_num)
{
	long long int	*double_to_int;
	char			sign;

	double_to_int = (long long int*)&check_num;
	sign = (char)(*double_to_int >> 63);
	if (sign == 0)
		return (0);
	else
		return (1);
}
