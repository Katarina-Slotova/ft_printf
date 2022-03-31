/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:03:36 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:17:11 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
		|| c == 'u' || c == 'x' || c == 'X' || c == 'f' || c == '%')
		return (1);
	else
		return (0);
}

int	conversion_identifier(va_list *ap, t_specs *utils)
{
	if (utils->c == 'c')
		return (conv_c(ap, utils));
	if (utils->c == 's')
		return (conv_s(ap, utils));
	if (utils->c == 'p')
		return (conv_p(ap, utils));
	if (utils->c == 'd' || utils->c == 'i')
		return (conv_d_i(ap, utils));
	if (utils->c == 'o')
		return (conv_o(ap, utils));
	if (utils->c == 'u')
		return (conv_u(ap, utils));
	if (utils->c == 'x' || utils->c == 'X')
		return (conv_x(ap, utils));
	if (utils->c == 'f')
		return (conv_f(ap, utils));
	if (utils->c == '%')
		return (conv_percent(utils));
	return (0);
}

int	conversion_solver(const char *format, va_list *ap, t_specs *utils)
{
	int		i;
	int		i_flags;
	int		result;

	i = 1;
	i_flags = 0;
	result = 0;
	utils->flags = ft_strnew(100);
	while (format[i] && !is_conversion(format[i]))
	{
		if (is_flag(format[i]))
			utils->flags[i_flags++] = format[i];
		i++;
	}
	utils->c = format[i];
	result = conversion_identifier(ap, utils);
	free(utils->flags);
	return (result);
}
