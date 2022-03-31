/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:57:26 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:16:50 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_hex(uintmax_t num, int base, t_specs *utils)
{
	char	*str;
	int		i;

	if (base < 2 || base > 16)
		return (NULL);
	i = ft_numlen_base_u(num, base);
	str = ft_strnew(i);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (num >= (uintmax_t)base && str[i] != '-')
	{
		str[i--] = ft_base_hex(num, base, utils->c);
		num = num / base;
	}
	if (num <= 9)
		str[i--] = ft_base_hex(num, base, utils->c);
	else
		str[i--] = ft_base_hex(num, base, utils->c);
	return (str);
}

int	ft_iszero(t_specs *utils)
{
	int	i;
	int	index_zero;
	int	index_comp;

	i = 0;
	index_zero = -1;
	index_comp = -1;
	while (utils->flags[i] && utils->flags[i] != '.')
	{
		if (utils->flags[i] == '0')
			index_zero = i;
		if (utils->flags[i] >= '1' && utils->flags[i] <= '9')
			index_comp = i;
		if ((index_zero < index_comp) && index_zero != -1)
			return (1);
		i++;
	}
	return (0);
}

char	*dio_width_emptyspaces(t_specs *utils, char *final_num)
{
	if (utils->empty_spaces > 0)
	{
		while (utils->empty_spaces-- > 0)
		{
			if (ft_iszero(utils) && !ft_strchr(utils->flags, '.'))
				final_num = ft_strjoin_free_s2("0", final_num);
			else
				final_num = ft_strjoin_free_s1(final_num, " ");
		}
	}
	return (final_num);
}

char	*f_width_emptyspaces(char *final_num, char *print_num, t_specs *utils)
{
	while (utils->empty_spaces > 0)
	{
		if (ft_iszero(utils) && !ft_strstr(print_num, "in")
			&& !(ft_strstr(print_num, "na")))
			final_num = ft_strjoin_free_s2("0", final_num);
		else
			final_num = ft_strjoin_free_s2(" ", final_num);
		utils->empty_spaces--;
	}
	return (final_num);
}

char	*ft_check_inf_nan(char *print_num, long double check_num,
t_specs *utils)
{
	double	x;
	double	y;
	double	z;

	x = 1;
	y = 0;
	z = -1;
	if (check_num == x / y)
		print_num = ft_strdup("inf");
	else if (check_num == z / y)
		print_num = ft_strdup("-inf");
	else if (check_num != check_num)
		print_num = ft_strdup("nan");
	else
		print_num = ft_itoa_float(check_num, utils->precision);
	return (print_num);
}
