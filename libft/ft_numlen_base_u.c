/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_base_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:23:33 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:24:03 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen_base_u(unsigned long long int num, int base)
{
	int	len;
	
	len = 1;
	while (num / base > 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}
