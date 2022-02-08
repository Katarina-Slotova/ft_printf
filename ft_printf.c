/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by katarinka         #+#    #+#             */
/*   Updated: 2022/02/08 19:14:37 by katarinka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

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

int	is_flag(char c)
{
	if (c == 'h' || c == 'l' || c == '#' || c == '-' || c == '+' || c == '0' \
	|| c == '.' || c == ' ' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

int	conversion_solver(const char *format, va_list *ap)
{
	int		i;
	char	conversion;
	char	*flags_collector;
	int		i_flags;

	i = 1;
	i_flags = 0;
	flags_collector = (char *)malloc(sizeof(char));
	while (format[i] && !is_conversion(format[i]))
	{
		if (is_flag(format[i]))
			flags_collector[i_flags++] = format[i];
		i++;
	}
	conversion = format[i];
	if (conversion == 'c')
		return (conv_c(ap, flags_collector));
 	if (conversion == 's')
		return (conv_s(ap, flags_collector));
	if (conversion == 'p')
		return (conv_p(ap, flags_collector));
/*	if (conversion == 'd')
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
		return (conv_f()); */
	return (0);
}

int	conv_c(va_list *ap, char *flags_collector)
{
	char	c;
	
	if (flags_collector)
		printf("%s", flags_collector);
	c = va_arg(*ap, int);
	ft_putchar(c);
	return(1);
}

int	conv_s(va_list *ap, char *flags_collector)
{
	char	*check_str;
	char	*print_str;
	int		len;
	
	if (flags_collector)
		printf("%s", flags_collector);
	check_str = va_arg(*ap, char*);
	if (check_str == NULL)
		print_str = ft_strdup("(null)");
	else
		print_str = ft_strdup(check_str);
	ft_putstr(print_str);
	len = ft_strlen(print_str);
	free(print_str);
	return(len);
}

int	ft_ptrlen(uintptr_t print_ptr)
{
	int	i;

	i = 0;
	while (print_ptr > 0)
	{
		print_ptr = print_ptr / 16;
		i++;
	}
	return (i);
}

void	ft_putptr(uintptr_t print_ptr)
{
	if (print_ptr >= 16)
	{
		ft_putptr(print_ptr / 16);
		ft_putptr(print_ptr % 16);
	}
	else
	{
		if (print_ptr < 10)
			ft_putchar(print_ptr + '0');
		else
			ft_putchar(print_ptr - 10 + 'a');
	}
	/* char	*str;
	int		len;
	
	len = ft_ptrlen(print_ptr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	while (print_ptr >= 16)
	{
		if (print_ptr % 16 < 10)
			ft_putchar(str[len--] = (print_ptr % 16) + '0');
		else
			ft_putchar(str[len--] = (print_ptr % 16) - 10 + 'a');
		print_ptr = print_ptr / 16;
	}
	if (print_ptr < 10)
		ft_putchar(str[len--] = print_ptr + '0');
	else
		ft_putchar(str[len--] = print_ptr - 10 + 'a');
	return (str); */
}

int	conv_p(va_list *ap, char *flags_collector)
{
	char	*ptr;
	int		len;
	
	if (flags_collector)
		printf("%s", flags_collector);
	len = 0;
	len = len + write(1, "0x", 2);
	ptr = va_arg(*ap, void*);
	if (ptr == 0)
		len = len + write(1, "0", 1);
	else
	{
		ft_putptr((uintptr_t)ptr);
		len = len + ft_ptrlen(*ptr);
	}
	return(len);
}

int	ft_printer(int printed_chars, char c)
{
	ft_putchar(c);
	return (printed_chars + 1);
}

int ft_printf(const char *format, ...)
{
	va_list	ap;
	int		char_counter;
	int		i;
	int		printed_chars;

	char_counter = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			char_counter += conversion_solver(&format[i], &ap);
		else
		{
			while ((is_conversion(format[i]) && format[i - 1] == '%') ||
			(is_flag(format[i]) && format[i - 1] == '%') ||
			(is_conversion(format[i]) && is_flag(format[i - 1])) ||
			(is_flag(format[i]) && is_flag(format[i - 1])))
				i++;
			printed_chars = ft_printer(printed_chars, format[i]);
			char_counter++;
		}
		i++;
	}
	va_end(ap);
	return (char_counter);
}
