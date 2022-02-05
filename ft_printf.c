/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by katarinka         #+#    #+#             */
/*   Updated: 2022/02/04 12:22:26 by katarinka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcharjoin(char *old_str, char c)
{
	char	*new_str;
	int		i;

	new_str = ft_strnew(ft_strlen(old_str) + 2);
	i = ft_strlen(new_str);
	ft_bzero(new_str, i);
	new_str = ft_strcpy(new_str, old_str);
	new_str[i] = c;
	return (new_str);
}

int	is_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o' \
	|| c == 'u' || c == 'x' || c == 'X' || c == 'f' || c == '%')
		return (1);
	else
		return (0);
}

int	conversion_solver(const char *format, va_list *ap)
{
	int		i;
	char	conversion;

	i = 0; // should I skip the " in the beginning? start at 1?
	while (format[i] && !is_conversion(format[i]))
	{
		//deal with the flags somewhere
		i++;
	}
	if (conversion == 'c')
		return (conv_c());
	if (conversion == 's')
		return (conv_s());
	if (conversion == 'p')
		return (conv_p());
	if (conversion == 'd')
		return (conv_d());
	if (conversion == 'i')
		return (conv_i());
	if (conversion == 'o')
		return (conv_o());
	if (conversion == 'u')
		return (conv_u());
	if (conversion == 'x')
		return (conv_x());
	if (conversion == 'X')
		return (conv_X());
	if (conversion == 'f')
		return (conv_f());
	return (0);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int		char_counter;
	int		i;
	char	*final_str;

	char_counter = 0;
	i = 0;
	final_str = (char *)malloc(sizeof(char));
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			//conversion handler -- maybe a separate function for that
			char_counter += conversion_solver(&format, &ap);
		else
		{
			//just add the printable character as received to the previously saved string of chars to be printed - 
			//write a strcharjoin function for this;
			final_str = ft_strcharjoin(final_str, format[i]);
			char_counter++;
		}
		i++;
	}
	write(1, final_str, ft_strlen(final_str));
	free(final_str);
	va_end(ap);
	return (char_counter);
}
