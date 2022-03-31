/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:56:39 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:38:02 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_cut_leftover(char *str, t_specs *utils)
{
	int		i;
	int		len;
	char	*final_str;

	i = 0;
	while (str[i] != '.')
		i++;
	len = i + utils->precision + 1;
	if (utils->precision == 0 && !ft_strchr(utils->flags, '#'))
		len--;
	while (str[i] && i < len)
		i++;
	final_str = ft_strsub(str, 0, i);
	free(str);
	return (final_str);
}

char	*ft_round_or_cut(char *print_num, long double check_num, t_specs *utils)
{
	long double		new_num;
	int				checker;

	checker = 0;
	if (check_num < 0)
	{
		checker = 1;
		check_num *= -1;
	}
	new_num = check_num * ft_x_to_power_n(utils->precision);
	if (new_num - (int)new_num > 0.5 || new_num - (int)new_num < -0.5)
		check_num = ft_round(check_num, utils->precision);
	else if (new_num - (int)new_num == 0.5 || new_num - (int)new_num == -0.5)
	{
		if (((int)new_num + 1) % 2 != 0)
			check_num = new_num / ft_x_to_power_n(utils->precision);
		else
			check_num = ft_round(check_num, utils->precision);
	}
	else
		check_num = ft_round(check_num, utils->precision);
	if (checker == 1)
		check_num *= -1;
	print_num = ft_check_inf_nan(print_num, check_num, utils);
	return (print_num);
}

char	*ft_f_precision(char *print_num, t_specs *utils)
{
	char	*final_num;

	utils->empty_spaces = 0;
	if (ft_strcmp(print_num, "+0") == 0 && utils->precision == 0)
		final_num = ft_strdup("+");
	else if ((int)ft_strlen(print_num) <= utils->precision)
	{
		final_num = ft_strnew(utils->precision);
		utils->empty_spaces = utils->precision - ft_strlen(print_num);
		if (ft_strchr(utils->flags, ' ') || (ft_strchr(utils->flags, '+')))
			utils->empty_spaces--;
		while (utils->empty_spaces > 0)
		{
			final_num = ft_strjoin_free_s2(" ", final_num);
			utils->empty_spaces--;
		}
		final_num = ft_strjoin_free_s2(print_num, final_num);
	}
	else
		final_num = ft_strdup(print_num);
	final_num = ft_cut_leftover(final_num, utils);
	free(print_num);
	return (final_num);
}

char	*ft_f_manager(char *print_num, long double check_num, int is_neg,
t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr("0+-. ", utils->flags[i]))
		i++;
	if (ft_strchr(print_num, '-'))
		print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	if (ft_strcmp(print_num, "inf") != 0 && ft_strcmp(print_num, "-inf") != 0
		&& ft_strcmp(print_num, "nan") != 0)
		print_num = ft_f_precision(print_num, utils);
	if (check_num < 0)
			print_num = ft_strjoin_free_s2("-", print_num);
	if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i])
		|| ft_iszero(utils))
		print_num = manage_f_width(print_num, check_num, i, utils);
	if (is_neg == 1 && !ft_strchr(print_num, '-'))
		print_num = manage_f_width_neg(print_num, i, utils);
	if (ft_strchr(utils->flags, '+') && is_neg == 0
		&& !ft_strstr(print_num, "na") && !ft_strstr(print_num, "+"))
		print_num = ft_strjoin_free_s2("+", print_num);
	if (ft_strchr(utils->flags, ' ') && is_neg == 0
		&& !ft_strchr(utils->flags, '+') && !ft_strstr(print_num, "na"))
		print_num = ft_strjoin_free_s2(" ", print_num);
	return (print_num);
}

int	conv_f(va_list *ap, t_specs *utils)
{
	char			*print_num;
	long double		check_num;
	int				len;
	int				is_neg;

	is_neg = 0;
	len = 0;
	print_num = NULL;
	check_num = ft_f_datatype(ap, utils);
	is_neg = ft_is_negative(check_num);
	if (ft_strchr(utils->flags, '.'))
		utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
	else
		utils->precision = 6;
	print_num = ft_round_or_cut(print_num, check_num, utils);
	print_num = ft_f_manager(print_num, check_num, is_neg, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}
