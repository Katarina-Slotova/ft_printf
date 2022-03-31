/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:57:15 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:24:44 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_manage_x_width(char *print_num, unsigned long long check_num,
t_specs *utils, int i)
{
	while (utils->flags[i] && (utils->flags[i] == '0'
			|| ft_isdigit(utils->flags[i]) != 1))
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	if (ft_strchr(utils->flags, '#') && check_num != 0
		&& !ft_strchr(utils->flags, '.'))
		print_num = ft_hashtag_x(print_num, utils);
	else
		print_num = ft_o_width(print_num, utils);
	return (print_num);
}

char	*ft_manage_x_precision(char *print_num, unsigned long long check_num,
t_specs *utils)
{
	utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
	print_num = ft_o_precision(print_num, utils);
	if (ft_strchr(utils->flags, '#') && check_num != 0 && utils->c == 'x')
		print_num = ft_strjoin_free_s2("0x", print_num);
	else if (ft_strchr(utils->flags, '#') && check_num != 0 && utils->c == 'X')
		print_num = ft_strjoin_free_s2("0X", print_num);
	return (print_num);
}

char	*ft_x_manager(char *print_num, unsigned long long check_num,
t_specs *utils)
{
	int		i;

	i = 0;
	if (ft_strchr("#-.", utils->flags[i]))
		i++;
	if (ft_strchr(utils->flags, '.'))
		print_num = ft_manage_x_precision(print_num, check_num, utils);
	if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i]))
		print_num = ft_manage_x_width(print_num, check_num, utils, i);
	else if (ft_strchr(utils->flags, '#') && check_num != 0
		&& !ft_strchr(utils->flags, '.'))
	{
		if (utils->c == 'x')
			print_num = ft_strjoin_free_s2("0x", print_num);
		else if (utils->c == 'X')
			print_num = ft_strjoin_free_s2("0X", print_num);
	}
	return (print_num);
}

int	conv_x(va_list *ap, t_specs *utils)
{
	char					*print_num;
	unsigned long long int	check_num;
	int						len;

	len = 0;
	check_num = ft_oux_datatype(ap, utils);
	print_num = ft_itoa_hex(check_num, 16, utils);
	print_num = ft_x_manager(print_num, check_num, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}
