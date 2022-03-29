/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:30:53 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:31:26 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_base_hex(unsigned int num, int base, char conversion)
{
	char	*max_base_chars;
	int		i;

	if (conversion == 'X')
		max_base_chars = "0123456789ABCDEF";
	else
		max_base_chars = "0123456789abcdef";
	i = num % base;
	return (max_base_chars[i]);
}
