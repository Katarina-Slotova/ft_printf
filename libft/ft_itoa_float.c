/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:10:25 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 17:13:25 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_after_point_to_ascii(long double double_num, int precision)
{
	char			*final_str;
	int				i;
	int				len;
	long long int	int_num;

	int_num = 0;
	i = 1;
	len = ft_len_double(double_num, precision);
	final_str = ft_strnew(len);
	if (!final_str)
		return (NULL);
	final_str[0] = '.';
	if (double_num < 0)
		double_num *= -1;
	while (i < len)
	{
		double_num = double_num * 10;
		int_num = double_num;
		final_str[i] = (int_num % 10) + '0';
		double_num -= int_num;
		i++;
	}
	return (final_str);
}

char	*ft_itoa_float(long double check_num, int precision)
{
	char			*before_point;
	char			*after_point;
	char			*final_str;
	long long int	num;

	num = check_num;
	before_point = ft_itoa_base(num, 10);
	after_point = ft_after_point_to_ascii(check_num, precision);
	final_str = ft_strjoin(before_point, after_point);
	free(before_point);
	free(after_point);
	return (final_str);
}
