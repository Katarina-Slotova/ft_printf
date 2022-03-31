/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 19:04:30 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_flag(char c)
{
	if (c == 'h' || c == 'l' || c == 'L' || c == '#' || c == '-' || c == '+'
		|| c == '0' || c == '.' || c == ' ' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

void	init_specs(t_specs *utils)
{
	utils->flags = NULL;
	utils->precision = 0;
	utils->width = 0;
	utils->empty_spaces = 0;
	utils->c = '\0';
	utils->in_conversion = 0;
}

int	ft_print_reg_char(char format, int char_counter)
{
	ft_putchar(format);
	char_counter++;
	return (char_counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		char_counter;
	int		i;
	t_specs	*utils;

	char_counter = 0;
	i = -1;
	va_start(ap, format);
	utils = (t_specs *)malloc(sizeof(t_specs));
	init_specs(utils);
	while (format[++i])
	{
		if (format[i] == '%' && utils->in_conversion == 0)
		{
			utils->in_conversion = 1;
			char_counter += conversion_solver(&format[i], &ap, utils);
		}
		else if (utils->in_conversion == 0)
			char_counter = ft_print_reg_char(format[i], char_counter);
		else if (is_conversion(format[i]))
			utils->in_conversion = 0;
	}
	free(utils);
	va_end(ap);
	return (char_counter);
}
