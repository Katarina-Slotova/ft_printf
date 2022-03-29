/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:14:45 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 17:15:04 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_double(long double num, int precision)
{
	int i;

	i = 0;
	if (num < 0)
		i++;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i + precision + 1);
}
