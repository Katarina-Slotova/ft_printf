/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by katarinka         #+#    #+#             */
/*   Updated: 2022/02/16 14:16:10 by katarinka        ###   ########.fr       */
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
	if (c == 'h' || c == 'l' || c == 'L' || c == '#' || c == '-' || c == '+' \
	|| c == '0' || c == '.' || c == ' ' || ft_isdigit(c))
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
		return (conv_p(ap, flags_collector, conversion));
	if (conversion == 'd' || conversion == 'i')
		return (conv_d_i(ap, flags_collector));
	if (conversion == 'o')
		return (conv_o(ap, flags_collector));
	if (conversion == 'u')
		return (conv_u(ap, flags_collector));
	if (conversion == 'x' || conversion == 'X')
		return (conv_x(ap, flags_collector, conversion));
/*	if (conversion == 'X')
		return (conv_X(ap, flags_collector)); */
	if (conversion == 'f')
		return (conv_f(ap, flags_collector));
	if (conversion == '%')
		return (conv_percent());
	return (0);
}

////////////////////////////////////////////CONV_%////////////////////////////////////////////////////////////////

int	conv_percent()
{
	write(1, "%", 1);
	return (1);
}

////////////////////////////////////////////CONV_C////////////////////////////////////////////////////////////////

int	ft_char_width(char c, char *flags, int width)
{
	int	total_width;
 
	total_width = width;
	if (ft_strchr(flags, '-'))
	{
		ft_putchar(c);
		width--;
		while(width > 0)
		{
			ft_putchar(' ');
			width--;
		}
	}
	else
	{
		while(width > 1)
		{
			ft_putchar(' ');
			width--;
		}
		ft_putchar(c);
	}
	return (total_width);
}

int	ft_char_manager(char c, char *flags)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	if (flags)
	{
		if (ft_strchr("-", flags[i]))
			i++;
		if (ft_isdigit(flags[i]))
			width = ft_atoi(flags + i);
		return (ft_char_width(c, flags, width));
	}
	else
	{
		ft_putchar(c);
		return (1);
	}
}

int	conv_c(va_list *ap, char *flags_collector)
{
	char	c;
	int		len;
	
	len = 0;
	c = va_arg(*ap, int);
	len = ft_char_manager(c, flags_collector);
	return(len);
}

////////////////////////////////////////////CONV_S////////////////////////////////////////////////////////////////

char	*ft_str_width_minus(char *flags, char *str, char *final_str, int empty_spaces)
{
	if (ft_strchr(flags, '-'))
	{
		final_str = ft_strcpy(final_str, str);
		while (empty_spaces > 0)
		{
			final_str = ft_strjoin(final_str, " ");
			empty_spaces--;
		}
	}
	else
	{
		while (empty_spaces > 0)
		{
			final_str = ft_strjoin(final_str, " ");
			empty_spaces--;
		}
		final_str = ft_strjoin(final_str, str);
	}
	return (final_str);
}

char	*ft_str_width(char *str, char *flags, int width)
{
	char	*final_str;
	int		empty_spaces;
	int		i;

	i = 0;
	empty_spaces = 0;
	if ((int)ft_strlen(str) < width)
	{
		final_str = ft_strnew(width);
		empty_spaces = width - ft_strlen(str);
		final_str = ft_str_width_minus(flags, str, final_str, empty_spaces);
	}
	else
		final_str = ft_strdup(str);
	free(str);
	return (final_str);
}

char	*ft_str_precision(char *str, int precision)
{
	char	*final_str;
	int		i;

	i = 0;
	if ((int)ft_strlen(str) > precision)
		final_str = ft_strsub(str, 0, precision);
	else
		final_str = ft_strdup(str);
	free(str);
	return (final_str);
}

char	*ft_str_manager(char *str, char *flags)
{
	int	i;
	int width;
	int precision;

	i = 0;
	width = 0;
	precision = 0;
	if (flags)
	{
	 	if (ft_strchr("-.", flags[i]))
			i++;
		if (ft_strchr(flags, '.'))
		{
			if (ft_isdigit(flags[i]) || ft_isdigit(flags[++i]))
				precision = ft_atoi(flags + i);
			str = ft_str_precision(str, precision);
		}
		else if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
		{
			width = ft_atoi(flags + i);
			str = ft_str_width(str, flags, width);
		}
	}
	return (str);
}

int	conv_s(va_list *ap, char *flags_collector)
{
	char	*check_str;
	char	*print_str;
	int		len;
	
	/* if (flags_collector)
		printf("%s\n", flags_collector); */
	check_str = va_arg(*ap, char*);
	if (check_str == NULL)
		print_str = ft_strdup("(null)");
	else
		print_str = ft_strdup(check_str);
	print_str = ft_str_manager(print_str, flags_collector);
	ft_putstr(print_str);
	len = ft_strlen(print_str);
	free(print_str);
	return(len);
}

////////////////////////////////////////////CONV_O////////////////////////////////////////////////////////////////

int	ft_numlen_base_u(uintmax_t num, int base)
{
	int	len;
	
	len = 1;
	while (num / base > 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}

char	ft_base_u(unsigned int num, int base)
{
	char	*max_base_chars;
	int		i;

	max_base_chars = "0123456789";
	i = num % base;
	return (max_base_chars[i]);
}

char	*ft_itoa_base_u(unsigned int num, int base)
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
	while (i >= 0 && str[i] != '-')
	{
		str[i] = ft_base_u(num, base);
		num = num / base;
		i--;
	}
	return (str);
}

int	conv_o(va_list *ap, char *flags_collector)
{
	char	*print_num;
	int		check_num;
	int		len;

	if (flags_collector)
		printf("%s", flags_collector);
	len = 0;
	check_num = va_arg(*ap, unsigned int);
	print_num = ft_itoa_base_u(check_num, 8);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_U////////////////////////////////////////////////////////////////

char	*ft_itoa_dbase_u(uintmax_t num, int base)
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
	while (i >= 0 && str[i] != '-')
	{
		str[i] = ft_base_u(num, base);
		num = num / base;
		i--;
	}
	return (str);
}

int	conv_u(va_list *ap, char *flags_collector)
{
	char	*print_num;
	int		check_num;
	int		len;

	if (flags_collector)
		printf("%s", flags_collector);
	len = 0;
	check_num = va_arg(*ap, unsigned int);
	print_num = ft_itoa_dbase_u(check_num, 10);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_x_X////////////////////////////////////////////////////////////////

char	ft_base_hex(unsigned int num, int base, char conversion)
{
	char	*max_base_chars;
	int		i;

	if (conversion == 'X')
		max_base_chars = "0123456789ABCDEF";
	else
		max_base_chars = "0123456789abcdef";
	i = num % base;
	return (max_base_chars[i]);
}

char	*ft_itoa_hex(uintmax_t num, int base, char conversion)
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
	while (num >= base && str[i] != '-')
	{
		str[i--] = ft_base_hex(num, base, conversion);
		num = num / base;
	}
	if (num <= 9)
		str[i--] = ft_base_hex(num, base, conversion);
	else
		str[i--] = ft_base_hex(num, base, conversion);
	return (str);
}

int	conv_x(va_list *ap, char *flags_collector, char conversion)
{
	char	*print_num;
	int		check_num;
	int		len;

	if (flags_collector)
		printf("%s", flags_collector);
	len = 0;
	check_num = va_arg(*ap, unsigned int);
	print_num = ft_itoa_hex(check_num, 16, conversion);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_P////////////////////////////////////////////////////////////////

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

char	*ft_ptr_width(char *ptr, char *flags, int width)
{
	char	*final_str;
	int		empty_spaces;
	
	empty_spaces = 0;
	if ((int)ft_strlen(ptr) < width)
	{
		final_str = ft_strnew(width);
		empty_spaces = width - (int)ft_strlen(ptr);
		if (ft_strchr(flags, '-'))
		{
			final_str = ft_strcpy(final_str, ptr);
			while (empty_spaces > 0)
			{
				final_str = ft_strjoin(final_str, " ");
				empty_spaces--;
			}
		}
		else
		{
			while (empty_spaces > 0)
			{
				final_str = ft_strjoin(final_str, " ");
				empty_spaces--;
			}
			final_str = ft_strjoin(final_str, ptr);
		}
	}
	else
		final_str = ft_strdup(ptr);
	return (final_str);
}

char	*ft_ptr_manager(char *ptr, char *flags)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	if (ft_strchr("-", flags[i]))
		i++;
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
	{
		width = ft_atoi(flags + i);
		ptr = ft_ptr_width(ptr, flags, width);
	}
	return (ptr);
}

int	conv_p(va_list *ap, char *flags_collector, char conversion)
{
	void	*ptr;
	char	*final_ptr;
	int		len;
	
	ptr = va_arg(*ap, void*);
	final_ptr = ft_itoa_hex((uintptr_t)ptr, 16, conversion);
	final_ptr = ft_strjoin("0x", final_ptr);
	if (flags_collector)
		final_ptr = ft_ptr_manager(final_ptr, flags_collector);
	ft_putstr(final_ptr);
	len = ft_strlen(final_ptr);
	free(final_ptr);
	return(len);
}

////////////////////////////////////////////CONV_D_I////////////////////////////////////////////////////////////////

int	ft_numlen_dibase(long num, int base)
{
	int	len;
	
	len = 0;
	if (num < 0)
		len++;
	while (num)
	{
		num = num / base;
		len++;
	}
	return (len);
}

char	ft_base(long int num, int base)
{
	char	*max_base_chars;
	int		i;

	max_base_chars = "0123456789";
	i = num % base;
	if (i < 0)
		i = i * -1;
	return (max_base_chars[i]);
}

char	*ft_itoa_dibase(long int num, int base)
{
	char	*str;
	int		i;

	if (base < 2 || base > 16)
		return (NULL);
	i = ft_numlen_dibase(num, base);
	str = ft_strnew(i);
	if (!str)
		return (NULL);
	if (num < 0)
		str[0] = '-';
	str[i--] = '\0';
	while (i >= 0 && str[i] != '-')
	{
		str[i] = ft_base(num, base);
		num = num / base;
		i--;
	}
	return (str);
}

int	conv_d_i(va_list *ap, char *flags_collector)
{
	char	*print_num;
	int		check_num;
	int		len;

	if (flags_collector)
		printf("%s", flags_collector);
	len = 0;
	check_num = va_arg(*ap, int);
	print_num = ft_itoa_dibase(check_num, 10);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_F////////////////////////////////////////////////////////////////

char	*ft_cut_leftover(char *str, int precision)
{
	int		i;
	int		len;
	char	*final_str;

	i = 0;
	while (str[i] != '.')
		i++;
	len = i + precision + 1;
	while (str[i] && i < len)
		i++;
	final_str = ft_strsub(str, 0, i);
	free(str);
	return (final_str);
}

long double	ft_round(long double check_num, int precision)
{
	long double	rounded_num;
	long double	rounder;

	rounder = .5;
	while (precision > 0)
	{
		rounder = rounder / 10;
		precision--;
	}
	if (check_num >= 0)
		rounded_num = check_num + rounder;
	else
		rounded_num = check_num - rounder;
	return (rounded_num);
}

static int	ft_len_double(long n, int precision)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i + precision + 1);
}

char	*ft_float_convertor(long double check_num, long int num, int precision)
{
	char	*final_str;
	int		i;
	int		len;

	i = 1;
	len = ft_len_double(check_num, precision);
	final_str = ft_strnew(len);
	if (!final_str)
		return (NULL);
	final_str[0] = '.';
	if (check_num < 0)
	{
		check_num = check_num * -1;
		num = num * -1;
	}
	num = check_num - num;
	while (i < len)
	{
		check_num = check_num * 10;
		num = check_num;
		final_str[i] = (num % 10) + '0';
		i++;
	}
	return (final_str);
}

char	*ft_itoa_float(long double check_num, int precision)
{
	char		*before_point;
	char		*after_point;
	char		*final_str;
	long int	num;

	num = check_num;
	before_point = ft_itoa_dibase(num, 10);
	after_point = ft_float_convertor(check_num, num, precision);
	final_str = ft_strjoin(before_point, after_point);
	free(before_point);
	free(after_point);
	return (final_str);
}

int	conv_f(va_list *ap, char *flags_collector)
{
	char			*print_num;
	long double		check_num;
	int				len;
	int				precision;

	if (flags_collector)
		printf("%s", flags_collector);
	if (ft_strchr(flags_collector, '.'))
		precision = ft_atoi(ft_strchr(flags_collector, '.') + 1);
	else
		precision = 6;
	len = 0;
	if (ft_strchr(flags_collector, 'L'))
		check_num = va_arg(*ap, long double);
	else
		check_num = va_arg(*ap, double);
	check_num = ft_round(check_num, precision);
	print_num = ft_itoa_float(check_num, precision);
	print_num = ft_cut_leftover(print_num, precision);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////PRINTF////////////////////////////////////////////////////////////////

int	ft_printer(int printed_chars, char c)
{
	ft_putchar(c);
	return (printed_chars);
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
