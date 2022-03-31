/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_prec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:14:47 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:21:11 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*di_width_above_prec(char *print_num, long long int check_num,
t_specs *utils)
{
	int	i;

	if ((utils->precision < utils->width) && ft_strchr(utils->flags, '.')
		&& !ft_strchr(utils->flags, '+') && !ft_strchr(utils->flags, '-')
		&& (int)ft_numlen_base(check_num, 10) < utils->precision)
		print_num = di_prec_not_zero(print_num, check_num, utils);
	else if (utils->precision == 0 && utils->width > utils->precision
		&& ft_strchr(utils->flags, '.'))
	{
		i = 0;
		if (print_num[i] == '0')
		{
			while (print_num[i] == '0' && print_num[i])
			{
				print_num[i] = ' ';
				i++;
			}
		}
	}
	return (print_num);
}

char	*ft_di_precision(char *print_num, long long int check_num,
t_specs *utils)
{
	char	*final_num;
	int		zeroed_spaces;

	if (ft_strcmp(print_num, "0") == 0 && utils->precision == 0)
		final_num = ft_strnew(1);
	else if ((int)ft_strlen(print_num) < utils->precision)
	{
		final_num = ft_strnew(utils->precision);
		zeroed_spaces = utils->precision - ft_strlen(print_num);
		while (zeroed_spaces > 0)
		{
			final_num = ft_strjoin_free_s2("0", final_num);
			zeroed_spaces--;
		}
		final_num = ft_strjoin_free_s1(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
	if (ft_strchr(utils->flags, '+') && check_num >= 0)
		final_num = ft_strjoin_free_s2("+", final_num);
	if (ft_strchr(utils->flags, ' ') && !ft_strchr(utils->flags, '+')
		&& check_num >= 0)
		final_num = ft_strjoin_free_s2(" ", final_num);
	return (final_num);
}

char	*di_prec_not_zero(char *print_num, long long int check_num,
t_specs *utils)
{
	int		i;
	int		diff;
	char	*print_num2;

	diff = 0;
	i = 0;
	diff = utils->width - utils->precision;
	print_num2 = ft_strsub(print_num, diff, ft_strlen(print_num));
	while (diff > 0)
	{
		if (check_num < 0 && i == 0)
		{
			print_num2 = ft_strjoin_free_s2("-", print_num2);
			i = 1;
			diff--;
		}
		if (diff > 0)
			print_num2 = ft_strjoin_free_s2(" ", print_num2);
		diff--;
	}
	free(print_num);
	return (print_num2);
}
