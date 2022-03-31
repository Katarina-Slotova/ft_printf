/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:56:33 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:19:10 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*di_manage_precision(char *print_num, long long int check_num,
t_specs *utils)
{
	char	*print_num2;

	print_num2 = NULL;
	if (ft_strchr(print_num, '-'))
		print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	print_num2 = ft_di_precision(print_num, check_num, utils);
	if (check_num < 0)
		print_num2 = ft_strjoin_free_s2("-", print_num2);
	free(print_num);
	return (print_num2);
}

char	*di_manage_width(char *print_num, long long int check_num, int i,
t_specs *utils)
{
	if (ft_isdigit(utils->flags[i]) != 1)
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	print_num = ft_di_width(print_num, check_num, utils);
	return (print_num);
}

char	*ft_di_manager(char *print_num, long long int check_num, t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr("0+-. ", utils->flags[i]))
		i++;
	if (ft_strchr(utils->flags, '.'))
	{
		utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
		print_num = di_manage_precision(print_num, check_num, utils);
	}
	if (ft_strchr(utils->flags, '-') || (ft_isdigit(utils->flags[i])
			&& utils->flags[0] != '.') || ft_iszero(utils))
		print_num = di_manage_width(print_num, check_num, i, utils);
	if (ft_strchr(utils->flags, '+') && check_num >= 0
		&& !ft_strchr(print_num, '+'))
		print_num = ft_strjoin_free_s2("+", print_num);
	else if (ft_strchr(utils->flags, ' ') && check_num >= 0
		&& !ft_strchr(print_num, ' '))
		print_num = ft_strjoin_free_s2(" ", print_num);
	print_num = di_width_above_prec(print_num, check_num, utils);
	return (print_num);
}

int	conv_d_i(va_list *ap, t_specs *utils)
{
	char			*print_num;
	long long int	check_num;
	int				len;

	len = 0;
	check_num = ft_di_datatype(ap, utils);
	print_num = ft_itoa_base(check_num, 10);
	print_num = ft_di_manager(print_num, check_num, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}
