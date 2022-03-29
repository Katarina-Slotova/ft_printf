/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:26:34 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_base_u(unsigned long long int num, int base)
{
	char	*max_base_chars;
	int		i;

	max_base_chars = "0123456789";
	i = num % base;
	return (max_base_chars[i]);
}
