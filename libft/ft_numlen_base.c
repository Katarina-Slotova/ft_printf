/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:39:09 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:29:37 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen_base(long long int num, int base)
{
	int	len;

	len = 0;
	if (num < 0 || num == 0)
		len++;
	while (num)
	{
		num = num / base;
		len++;
	}
	return (len);
}
