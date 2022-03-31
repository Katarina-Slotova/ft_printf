/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:57:11 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:19:41 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_u_manager(char *print_num, t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr("-.", utils->flags[i]))
		i++;
	if (ft_strchr(utils->flags, '.'))
	{
		utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
		print_num = ft_o_precision(print_num, utils);
	}
	if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i]))
	{
		while (utils->flags[i] && (utils->flags[i] == '0'
				|| ft_isdigit(utils->flags[i]) != 1))
			i++;
		utils->width = ft_atoi(&utils->flags[i]);
		if (utils->width < 0)
			utils->width = utils->width * -1;
		print_num = ft_o_width(print_num, utils);
	}
	return (print_num);
}

int	conv_u(va_list *ap, t_specs *utils)
{
	char						*print_num;
	unsigned long long int		check_num;
	int							len;

	len = 0;
	check_num = ft_oux_datatype(ap, utils);
	print_num = ft_itoa_base_u(check_num, 10);
	print_num = ft_u_manager(print_num, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}
