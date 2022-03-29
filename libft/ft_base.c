/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:43:02 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:43:22 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_base(long long int num, int base)
{
	char	*max_base_chars;
	int		i;

	max_base_chars = "0123456789";
	i = num % base;
	if (i < 0)
		i = i * -1;
	return (max_base_chars[i]);
}
