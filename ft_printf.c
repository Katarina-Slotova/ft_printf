/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/25 14:58:04 by kslotova         ###   ########.fr       */
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

int	conversion_identifier(char conversion, char *flags, va_list *ap)
{
	if (conversion == 'c')
		return (conv_c(ap, flags));
	if (conversion == 's')
		return (conv_s(ap, flags));
	if (conversion == 'p')
		return (conv_p(ap, flags, conversion));
	if (conversion == 'd' || conversion == 'i')
		return (conv_d_i(ap, flags));
	if (conversion == 'o')
		return (conv_o(ap, flags));
	if (conversion == 'u')
		return (conv_u(ap, flags));
	if (conversion == 'x' || conversion == 'X')
		return (conv_x(ap, flags, conversion));
	if (conversion == 'f')
		return (conv_f(ap, flags));
	if (conversion == '%')
		return (conv_percent(flags));
	return (0);
}

int	conversion_solver(const char *format, va_list *ap)
{
	int		i;
	char	conversion;
	char	*flags_collector;
	int		i_flags;
	int		result;

	i = 1;
	i_flags = 0;
	result = 0;
	flags_collector = ft_strnew(20);
	while (format[i] && !is_conversion(format[i]))
	{
		if (is_flag(format[i]))
			flags_collector[i_flags++] = format[i];
		i++;
	}
	conversion = format[i];
	result = conversion_identifier(conversion, flags_collector, ap);
	free(flags_collector);
	return (result);
}

////////////////////////////////////////////GENERAL FUNCTIONS////////////////////////////////////////////////////////////////

unsigned long long int	ft_oux_datatype(va_list *ap, char *flags)
{
	if (ft_strstr(flags, "hh"))
		return (unsigned char)va_arg(*ap, unsigned int);
	else if (ft_strchr(flags, 'h'))
		return (unsigned short int)va_arg(*ap, unsigned int);
	else if (ft_strchr(flags, 'l'))
		return va_arg(*ap, unsigned long int);
	else if (ft_strstr(flags, "ll"))
		return va_arg(*ap, unsigned long long int);
	else
		return va_arg(*ap, unsigned int);
}

long long int	ft_di_datatype(va_list *ap, char *flags)
{
	if (ft_strstr(flags, "hh"))
		return (signed char)va_arg(*ap, int);
	else if (ft_strchr(flags, 'h'))
		return (short int)va_arg(*ap, int);
	else if (ft_strchr(flags, 'l'))
		return va_arg(*ap, long int);
	else if (ft_strstr(flags, "ll"))
		return va_arg(*ap, long long int);
	else
		return va_arg(*ap, int);
}

int	ft_iszero(char *flags)
{
	int	i;
	int index_zero;
	int	index_comp;

	i = 0;
	index_zero = -1;
	index_comp = -1;
	//printf("Flags: %s\n", flags);
	while (flags[i] && flags[i] != '.')
	{
		if (flags[i] == '0')
			index_zero = i;
		if (flags[i] >= '1' && flags[i] <= '9')
			index_comp = i;
		if ((index_zero < index_comp) && index_zero != -1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (s1 && s2)
	{
		if (ret != NULL)
		{
			i = 0;
			j = 0;
			while (s1[i])
			{
				ret[i] = s1[i];
				i++;
			}
			while (s2[j])
				ret[i++] = s2[j++];
			ret[i] = '\0';
			free(s1);
			return (ret);
		}
	}
	return (NULL);
}

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	//printf("This is ret value: %s\n", s2);
	ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (s1 && s2)
	{
		if (ret != NULL)
		{
			i = 0;
			j = 0;
			while (s1[i])
			{
				ret[i] = s1[i];
				i++;
			}
			while (s2[j])
				ret[i++] = s2[j++];
			ret[i] = '\0';
			free(s2);
			return (ret);
		}
	}
	return (NULL);
}

char	*dio_width_emptyspaces(int empty_spaces, char *flags, char *final_num)
{
	if (empty_spaces > 0)
	{
		while (empty_spaces-- > 0)
		{
			if (ft_iszero(flags) && !ft_strchr(flags, '.'))
				final_num = ft_strjoin_free_s2("0", final_num);
			else 
				final_num = ft_strjoin_free_s1(final_num, " ");
		}
	}
	return (final_num);
}

////////////////////////////////////////////CONV_C////////////////////////////////////////////////////////////////

void	ft_handle_minus(char c, int width)
{
	ft_putchar(c);
	width--;
	while(width > 0)
	{
		ft_putchar(' ');
		width--;
	}
}

int	ft_char_width(char c, char *flags, int width)
{
	int	total_width;

	total_width = width;
	if (ft_strchr(flags, '-'))
		ft_handle_minus(c, width);
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
	if (ft_strcmp(flags, "") != 0)
	{
		if (ft_strchr("-", flags[i]))
			i++;
		if (ft_isdigit(flags[i]))
			width = ft_atoi(flags + i);
		else
		{
			ft_putchar(c);
			return (1);
		}
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
	return (len);
}

////////////////////////////////////////////CONV_%////////////////////////////////////////////////////////////////

int	ft_percent_width(char *flags, int width)
{
	int	total_width;

	total_width = width;
	if (ft_strchr(flags, '-'))
	{
		write(1, "%", 1);
		width--;
		while(width-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while(width-- > 1)
		{
			if (ft_strchr(flags, '0'))
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
		write(1, "%", 1);
	}
	return (total_width);
}

int	ft_percent_manager(char *flags)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
	{
		if (ft_strchr("-", flags[i]))
			i++;
		if (ft_isdigit(flags[i]))
			width = ft_atoi(flags + i);
		return (ft_percent_width(flags, width));
	}
	else
	{
		write(1, "%", 1);
		return (1);
	}
}

int	conv_percent(char *flags_collector)
{
	int		len;

	len = 0;
	len = ft_percent_manager(flags_collector);
	return (len);
}
////////////////////////////////////////////CONV_S////////////////////////////////////////////////////////////////

char	*ft_str_width_minus(char *flags, char *str, char *final_str, int empty_spaces)
{
	if (ft_strchr(flags, '-'))
	{
		final_str = ft_strcpy(final_str, str);
		while (empty_spaces > 0)
		{
			final_str = ft_strjoin_free_s1(final_str, " ");
			empty_spaces--;
		}
	}
	else
	{
		while (empty_spaces > 0)
		{
			final_str = ft_strjoin_free_s1(final_str, " ");
			empty_spaces--;
		}
		final_str = ft_strjoin_free_s1(final_str, str);
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
	 	/* if (ft_strchr("-.", flags[i]))
			i++; */
		if (ft_strchr(flags, '.'))
		{
			precision = ft_atoi(ft_strchr(flags, '.') + 1);
			str = ft_str_precision(str, precision);
		}
		if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
		{
			width = ft_atoi(&flags[i]);
			if (width < 0)
				width *= -1;
			str = ft_str_width(str, flags, width);
		}
	}
	//printf("This is the final string: <<%s>>\n", str);
	return (str);
}

int	conv_s(va_list *ap, char *flags_collector)
{
	char	*check_str;
	char	*print_str;
	int		len;
	
/* 	if (flags_collector)
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

int	ft_numlen_base_u(unsigned long long int num, int base)
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

char	ft_base_u(unsigned long long int num, int base)
{
	char	*max_base_chars;
	int		i;

	max_base_chars = "0123456789";
	i = num % base;
	return (max_base_chars[i]);
}

char	*ft_itoa_base_u(unsigned long long int num, int base)
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

char	*ft_o_width(char *print_num, char *flags, int width)
{
	char	*final_num;
	int		empty_spaces;

	if ((int)ft_strlen(print_num) < width)
	{
		empty_spaces = width - (int)ft_strlen(print_num);
		final_num = ft_strnew(width);
		if (ft_strchr(flags, '-'))
		{
			final_num = ft_strjoin_free_s1(final_num, print_num);
			while (empty_spaces-- > 0)
				final_num = ft_strjoin_free_s1(final_num, " ");
		}
		else
		{
			final_num = dio_width_emptyspaces(empty_spaces, flags, final_num);
			/* 	while (empty_spaces-- > 0)
			{
				if (ft_iszero(flags))
					final_num = ft_strjoin(final_num, "0");
				else
					final_num = ft_strjoin(final_num, " ");
			} */
			final_num = ft_strjoin_free_s1(final_num, print_num);
		}
	}
	else
		final_num = ft_strdup(print_num);
	free(print_num);
	return (final_num);
}

char	*ft_o_precision(char *print_num, int precision)
{
	char	*final_num;
	int		zeroed_spaces;
	
	//printf("This is precision: %d\n", precision);
	if (ft_strcmp(print_num, "0") == 0 && precision == 0)
		final_num = ft_strnew(1);
	else if ((int)ft_strlen(print_num) < precision)
	{
		final_num = ft_strnew(precision);
		zeroed_spaces = precision - ft_strlen(print_num);
		while (zeroed_spaces-- > 0)
			final_num = ft_strjoin_free_s2("0", final_num);
		final_num = ft_strjoin_free_s2(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
	//printf("This is final num: %s\n", final_num);
	return (final_num);	
}

char	*ft_manage_o_width(char *print_num, unsigned long long check_num, 
char *flags, int i)
{
	int	width;

	width = 0;
	while (flags[i] && ft_isdigit(flags[i]) != 1 && !ft_strchr(flags, 'h'))
		i++;
	width = ft_atoi(&flags[i]);
	if (width < 0)
		width *= -1;
	if (ft_strchr(flags, '#') && !ft_strchr(flags, '.') && check_num != 0)
		print_num = ft_strjoin_free_s2("0", print_num);
	print_num = ft_o_width(print_num, flags, width);
	return (print_num);
}

char	*ft_o_manager(char *print_num, unsigned long long check_num,
char *flags)
{
	int	precision;
	int	i;

	i = 0;
	precision = 0;
	//printf("The flag is <<%s>>\n", flags);
	if (ft_strchr("0-#.", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		if ((print_num[0] == '\0' || print_num[0] == '0') &&
		ft_strchr(flags, '#') && precision == 0)
			print_num = ft_strdup("0");
		else 
		{
			if (ft_strchr(flags, '#'))
				print_num = ft_strjoin_free_s2("0", print_num);
			print_num = ft_o_precision(print_num, precision);
		}
	}
	if (ft_strchr(flags, '-') || ft_isdigit(*flags) || ft_strchr(flags, '#'))
		print_num = ft_manage_o_width(print_num, check_num, flags, i);
	return (print_num);
}

int	conv_o(va_list *ap, char *flags_collector)
{
	char						*print_num;
	unsigned long long int		check_num;
	int							len;

	len = 0;
	check_num = ft_oux_datatype(ap, flags_collector);
	print_num = ft_itoa_base_u(check_num, 8);
	print_num = ft_o_manager(print_num, check_num, flags_collector);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_U////////////////////////////////////////////////////////////////

char	*ft_itoa_dbase_u(unsigned long long int num, int base)
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

char	*ft_u_manager(char *print_num, char *flags)
{
	int	width;
	int	precision;
	int	i;

	i = 0;
	precision = 0;
	width = 0;
	if (ft_strchr("-.", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		print_num = ft_o_precision(print_num, precision);
	}
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
	{
		while (flags[i] && (ft_iszero(&flags[i]) || ft_isdigit(flags[i]) != 1))
			i++;
		width = ft_atoi(&flags[i]);
		if (width < 0)
			width = width * -1;
		print_num = ft_o_width(print_num, flags, width);
	}
	return (print_num);
}

int	conv_u(va_list *ap, char *flags_collector)
{
	char						*print_num;
	unsigned long long int		check_num;
	int							len;

/* 	if (flags_collector)
		printf("%s", flags_collector); */
	len = 0;
	check_num = ft_oux_datatype(ap, flags_collector);
	print_num = ft_itoa_dbase_u(check_num, 10);
	print_num = ft_u_manager(print_num, flags_collector);
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
	while (num >= (uintmax_t)base && str[i] != '-')
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

char	*ft_hashtag_width_x(char *print_num, char *final_num, char *flags,
char conversion, int width)
{
	if (ft_iszero(flags) && !ft_strchr(flags, '-'))
	{
		print_num = ft_o_width(print_num, flags, width);
		print_num = ft_strsub(print_num, 2, ft_strlen(print_num));
	}
	if (conversion == 'x')
		final_num = ft_strjoin_free_s2("0x", print_num);
	else if (conversion == 'X')
		final_num = ft_strjoin_free_s2("0X", print_num);
	final_num = ft_o_width(final_num, flags, width);
	return (final_num);
}

char	*ft_hashtag_x(char *print_num, char conversion, char *flags, int w_or_p)
{
	char	*final_num;
	int		i;

	i = 0;
	if (print_num[0] == '\0' || print_num[0] == '0')
		final_num = ft_strdup("0");
	if (ft_strchr(flags, '.'))
	{
		final_num = ft_o_precision(print_num, w_or_p);
		if (conversion == 'x')
			final_num = ft_strjoin_free_s2("0x", print_num);
		else if (conversion == 'X')
			final_num = ft_strjoin_free_s2("0X", print_num);
	}
	if (ft_strchr(flags, '-') || ft_strchr(flags, ft_isdigit(*flags)))
		final_num = ft_hashtag_width_x(print_num, final_num, flags, conversion, 
		w_or_p);
	else
		if (conversion == 'x')
			final_num = ft_strjoin_free_s2("0x", print_num);
		else if (conversion == 'X')
			final_num = ft_strjoin_free_s2("0X", print_num);
	return (final_num);
}

char	*ft_manage_x_width(char *print_num, unsigned long long check_num, 
char *flags, char conv, int i)
{
	int	width;

	width = 0;
	while (flags[i] && (ft_iszero(&flags[i]) || ft_isdigit(flags[i]) != 1))
		i++;
	width = ft_atoi(&flags[i]);
	if (ft_strchr(flags, '#') && check_num != 0 && !ft_strchr(flags, '.'))
		print_num = ft_hashtag_x(print_num, conv, flags, width);
	else
		print_num = ft_o_width(print_num, flags, width);
	return (print_num);
}

char	*ft_x_manager(char *print_num, unsigned long long check_num, 
char *flags, char conv)
{
	int		precision;
	int		i;

	i = 0;
	if (ft_strchr("#-.", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		print_num = ft_o_precision(print_num, precision);
		if (ft_strchr(flags, '#') && check_num != 0 && conv == 'x')
			print_num = ft_strjoin_free_s2("0x", print_num);
		else if (ft_strchr(flags, '#') && check_num != 0 && conv == 'X')
			print_num = ft_strjoin_free_s2("0X", print_num);
	}
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
		print_num = ft_manage_x_width(print_num, check_num, flags, conv, i);
	else if (ft_strchr(flags, '#') && check_num != 0 && !ft_strchr(flags, '.'))
	{
		if (conv == 'x')
			print_num = ft_strjoin_free_s2("0x", print_num);
		else if (conv == 'X')
			print_num = ft_strjoin_free_s2("0X", print_num);
	}
	return (print_num);
}

int	conv_x(va_list *ap, char *flags_collector, char conversion)
{
	char						*print_num;
	unsigned long long int		check_num;
	int							len;

/* 	if (flags_collector)
		printf("<<<%s>>>", flags_collector); */
	len = 0;
	check_num = ft_oux_datatype(ap, flags_collector);
	print_num = ft_itoa_hex(check_num, 16, conversion);
	print_num = ft_x_manager(print_num, check_num, flags_collector, conversion);
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

char	*ft_manage_ptr_emptyspcs(char *final_str, int empty_spaces)
{
	while (empty_spaces > 0)
	{
		final_str = ft_strjoin_free_s2(" ", final_str);
		empty_spaces--;
	}
	return (final_str);
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
			final_str = ft_manage_ptr_emptyspcs(final_str, empty_spaces);
			final_str = ft_strjoin_free_s2(ptr, final_str);
		}
		else
		{
			final_str = ft_strcpy(final_str, ptr);
			final_str = ft_manage_ptr_emptyspcs(final_str, empty_spaces);
		}
	}
	else
		final_str = ft_strdup(ptr);
	free(ptr);
	return (final_str);
}

char	*ft_ptr_precision(char *ptr, int precision, int empty_spaces)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = ft_strnew(precision);
	if (ft_strequ(ptr, "0x0") && precision == 0)
	{
		free(ptr);
		return (ft_strdup("0x"));
	}
	else if ((int)ft_strlen(ptr) < precision)
	{
		while (empty_spaces > 0)
		{
			final_str = ft_strjoin_free_s2("0", final_str);
			empty_spaces--;
		}
		ptr = ft_strsub(ptr, 2, (int)ft_strlen(ptr));
		final_str = ft_strjoin_free_s1(final_str, ptr);
		final_str = ft_strjoin_free_s2("0x", final_str);
	}
	else
		final_str = ft_strdup(ptr);
	free(ptr);
	return (final_str);
}

char	*ft_ptr_manager(char *ptr, char *flags)
{
	int	i;
	int	width;
	int	precision;
	int	empty_spaces;

	i = 0;
	width = 0;
	precision = 0;
	if (ft_strchr("-.", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		empty_spaces = precision - (int)ft_strlen(ptr) + 2;
		ptr = ft_ptr_precision(ptr, precision, empty_spaces);
	}
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
	if (flags_collector)
	final_ptr = ft_strjoin_free_s2("0x", final_ptr);
		final_ptr = ft_ptr_manager(final_ptr, flags_collector);
	ft_putstr(final_ptr);
	len = ft_strlen(final_ptr);
	free(final_ptr);
	return(len);
}

////////////////////////////////////////////CONV_D_I////////////////////////////////////////////////////////////////

int	ft_numlen_dibase(long long int num, int base)
{
	int	len;
	
	len = 0;
	if (num < 0 || num == 0)
		len++;
	while (num)
	{
		num = num / base;
		len++;
	}
	return (len);
}

char	ft_base(long long int num, int base)
{
	char	*max_base_chars;
	int		i;

	max_base_chars = "0123456789";
	i = num % base;
	if (i < 0)
		i = i * -1;
	return (max_base_chars[i]);
}

char	*ft_itoa_dibase(long long int num, int base)
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

char	*di_width_flags(char *flags, long long int check_num, int width,
char *final_num)
{
	char	*final_num2;

	final_num2 = NULL;
	if (ft_strchr(flags, '+') && !ft_iszero(flags) && !ft_strchr(flags, '.')
	&& check_num >= 0)
	{
		final_num = ft_strsub(final_num, 1, width);
		final_num2 = ft_strjoin_free_s2("+", final_num);
	}
	else if ((ft_strchr(flags, '+') || ft_strchr(flags, ' ')) &&
	!ft_strchr(flags, '.') && ft_iszero(flags) && check_num >= 0)
	{
		final_num = ft_strsub(final_num, 1, width);
		if (ft_strchr(flags, '+'))
			final_num2 = ft_strjoin_free_s2("+", final_num);
		else if (ft_strchr(flags, ' ') && !ft_iszero(flags))
			final_num2 = ft_strjoin_free_s2(" ", final_num);
		else if (ft_strchr(flags, ' '))
			final_num2 = ft_strjoin_free_s2(" ", final_num);
		}
	else
	{
		final_num2 = ft_strdup(final_num);
		free(final_num);
	}
	return (final_num2);
}

char	*di_width_minusflag(char *final_num, char *print_num, char *flags,
long long int check_num, int empty_spaces)
{
	final_num = ft_strcpy(final_num, print_num);
	if (ft_strchr(flags, '+') && !ft_strchr(flags, '.'))
	{
		final_num = ft_strjoin_free_s2("+", final_num);
		empty_spaces--;
	}
	if (ft_strchr(flags, ' ') && !ft_strchr(flags, '.') && check_num >= 0)
	{
		final_num = ft_strjoin_free_s2(" ", final_num);
		empty_spaces--;
	}
	while (empty_spaces-- > 0)
		final_num = ft_strjoin_free_s1(final_num, " ");
	return (final_num);
}

char	*ft_di_negative_num(char *final_num, char *print_num, char *flags,
long long int check_num, int width, int empty_spaces)
{
 	char	*final_num2;

	final_num = dio_width_emptyspaces(empty_spaces, flags, final_num);
	final_num2 = di_width_flags(flags, check_num, width, final_num);
	if (check_num < 0 && ft_strchr(flags, '.'))
		final_num2 = ft_strjoin_free_s1(final_num2, "-");
	else
		final_num2 = ft_strjoin_free_s2("-", final_num2);
	//printf("final num2 is %s\n", final_num2);
	//printf("Print num is %s\n", print_num);
	//final_num2 = final_num3;
	print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	final_num2 = ft_strjoin_free_s2(final_num2, print_num);
	//printf("Final num = <<%s>>\n", final_num2);
	return (final_num2);
}

char	*ft_di_width(char *print_num, long long int check_num, char *flags,
int width)
{
	char	*final_num;
	int		empty_spaces;
	int		checker;
	
	checker = 0;
	//printf("Heerreeee\n");
	if ((int)ft_strlen(print_num) <= width)
	{
		checker = 1;
		empty_spaces = width - (int)ft_strlen(print_num);
		final_num = ft_strnew(width);
		if (ft_strchr(flags, '-'))
			final_num = di_width_minusflag(final_num, print_num, flags, check_num, empty_spaces);
		else if ((ft_iszero(flags) || ft_strchr(flags, '+')) && check_num < 0)
		{
			
			final_num = ft_di_negative_num(final_num, print_num, flags, check_num, width, empty_spaces);
		}
		else
		{
			final_num = dio_width_emptyspaces(empty_spaces, flags, final_num);
			final_num = di_width_flags(flags, check_num, width, final_num);
			final_num = ft_strjoin_free_s1(final_num, print_num);
		}
	}
	else
	{
		final_num = ft_strdup(print_num);
		free(print_num);
	}
	if (ft_strchr(flags, ' ') && !ft_strchr(flags, '.') && check_num >= 0
	&& checker == 0)
		final_num = ft_strjoin_free_s2(" ", final_num);
	return (final_num);
}

char	*ft_di_precision(char *print_num, char *flags, int precision, long long int check_num)
{
	char	*final_num;
	int		zeroed_spaces;

	if (ft_strcmp(print_num, "0") == 0 && precision == 0)
		final_num = ft_strnew(1);
	else if ((int)ft_strlen(print_num) < precision)
	{
		final_num = ft_strnew(precision);
		zeroed_spaces = precision - ft_strlen(print_num);
		while (zeroed_spaces > 0)
		{
			final_num = ft_strjoin_free_s2("0", final_num);
			zeroed_spaces--;
		}
		final_num = ft_strjoin_free_s1(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
 	if (ft_strchr(flags, '+') && check_num >= 0)
		final_num = ft_strjoin_free_s2("+", final_num);
	if (ft_strchr(flags, ' ') && !ft_strchr(flags, '+') && check_num >= 0)
		final_num = ft_strjoin_free_s2(" ", final_num);
	return (final_num);
}

char	*di_prec_not_zero(char *print_num, long long int check_num, 
int width, int precision)
{
	int	i;
	int	diff;
	char	*print_num2;

	diff = 0;
	i = 0;
	diff = width - precision;
	print_num2 = ft_strsub(print_num, diff, ft_strlen(print_num));
	//printf("OVER HERE print num is %s\n", print_num);
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

char	*di_width_above_prec(char *print_num, long long int check_num, 
char *flags, int width, int precision)
{
	int	i;

	if ((precision < width) && ft_strchr(flags, '.') && !ft_strchr(flags, '+') 
	&& !ft_strchr(flags, '-') &&
	(int)ft_numlen_dibase(check_num, 10) < precision)
		print_num = di_prec_not_zero(print_num, check_num, width, precision);
	else if (precision == 0 && width > precision && ft_strchr(flags, '.'))
	{
		i = 0;
		if (print_num[i] == '0')
			while (print_num[i] == '0' && print_num[i])
			{
				print_num[i] = ' ';
				i++;	
			}
	}
	return (print_num);
}

char	*di_manage_precision(char *print_num, long long int check_num, 
char *flags, int precision)
{
	char	*print_num2;
	
	print_num2 = NULL;
	if (ft_strchr(print_num, '-'))
		print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	print_num2 = ft_di_precision(print_num, flags, precision, check_num);
	if (check_num < 0)
		print_num2 = ft_strjoin_free_s2("-", print_num2);
	free(print_num);
	return (print_num2);
}

char	*ft_di_manager(char *print_num, long long int check_num, char *flags)
{
	int	width;
	int	precision;
	int	i;

	i = 0;
	width = 0;
	precision = 0;
	if (ft_strchr("0+-. ", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		print_num = di_manage_precision(print_num, check_num, flags, precision);
	}
	if (ft_strchr(flags, '-') || (ft_isdigit(flags[i]) && flags[0] != '.') || ft_iszero(flags))
	{
		if (ft_isdigit(flags[i]) != 1)
			i++;
		width = ft_atoi(&flags[i]);
		print_num = ft_di_width(print_num, check_num, flags, width);
	}
	if (ft_strchr(flags, '+') && check_num >= 0 && !ft_strchr(print_num, '+'))
		print_num = ft_strjoin_free_s2("+", print_num);
	else if (ft_strchr(flags, ' ') && check_num >= 0 &&
	!ft_strchr(print_num, ' '))
		print_num = ft_strjoin_free_s2(" ", print_num);
	print_num = di_width_above_prec(print_num, check_num, flags, width, precision);
	return (print_num);
}

int	conv_d_i(va_list *ap, char *flags_collector)
{
	char			*print_num;
	long long int	check_num;
	int				len;

	len = 0;
	check_num = ft_di_datatype(ap, flags_collector);
	print_num = ft_itoa_dibase(check_num, 10);
	print_num = ft_di_manager(print_num, check_num, flags_collector);
	while(1);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_F////////////////////////////////////////////////////////////////

char	*ft_cut_leftover(char *str, int precision, char *flags)
{
	int		i;
	int		len;
	char	*final_str;

	i = 0;
	while (str[i] != '.')
		i++;
	len = i + precision + 1;
 	if (precision == 0 && !ft_strchr(flags, '#'))
		len--;
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

static int	ft_len_double(long double n, int precision)
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

char	*ft_float_convertor(long double check_num, long long int num,
int precision)
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
		check_num = check_num - num;
		i++;
	}
	return (final_str);
}

char	*ft_itoa_float(long double check_num, int precision)
{
	char		*before_point;
	char		*after_point;
	char		*final_str;
	long long int	num;

	num = check_num;
	before_point = ft_itoa_dibase(num, 10);
	after_point = ft_float_convertor(check_num, num, precision);
	final_str = ft_strjoin(before_point, after_point);
	free(before_point);
	free(after_point);
	return (final_str);
}

char	*ft_f_precision(char *print_num, int precision, char *flags)
{
	char	*final_num;
	int		empty_spaces;

	empty_spaces = 0;
	if (ft_strcmp(print_num, "+0") == 0 && precision == 0)
		final_num = ft_strdup("+");
	else if ((int)ft_strlen(print_num) <= precision)
	{
		final_num = ft_strnew(precision);
		empty_spaces = precision - ft_strlen(print_num);
		if (ft_strchr(flags, ' ') || (ft_strchr(flags, '+')))
			empty_spaces--;
		while (empty_spaces > 0)
		{
			final_num = ft_strjoin_free_s2(" ", final_num);
			empty_spaces--;
		}
		final_num = ft_strjoin_free_s2(print_num, final_num);
	}
	else
		final_num = ft_strdup(print_num);
	
	final_num = ft_cut_leftover(final_num, precision, flags);
	free(print_num);
	return (final_num);
}

char	*f_width_emptyspcs(char *final_num, char *flags, int empty_spaces)
{
	while (empty_spaces > 0)
	{
		if (ft_iszero(flags))
			final_num = ft_strjoin_free_s2("0", final_num);
		else
			final_num = ft_strjoin_free_s2(" ", final_num);
		empty_spaces--;
	}
	return (final_num);
}

char	*ft_f_width(char *print_num, long double check_num, char *flags, int width)
{
	char	*final_num;
	int		i;
	int		empty_spaces;

	empty_spaces = 0;
	i = 0;
	if (((int)ft_strlen(print_num) < width))
	{
		empty_spaces = width - (int)ft_strlen(print_num);
		final_num = ft_strnew(width);
		if (ft_iszero(flags) && check_num >= 0 && (ft_strchr(flags, ' ') ||
		(ft_strchr(flags, '+'))))
			empty_spaces--;
		final_num = f_width_emptyspcs(final_num, flags, empty_spaces);
		if (ft_strchr(print_num, '-') && ft_strchr(final_num, '0'))
				print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
		final_num = ft_strjoin_free_s2(print_num, final_num);
		if (check_num < 0 && ft_strchr(final_num, '0') &&
		!ft_strchr(final_num, '-'))
			final_num = ft_strjoin_free_s2("-", final_num);
	}
	else
		final_num = ft_strdup(print_num);
	free(print_num);
	return (final_num);
}

char	*manage_f_width(char *print_num, long double check_num, char *flags, 
int width, int precision, int i)
{
	if (ft_isdigit(flags[i]) != 1)
		i++;
	width = ft_atoi(&flags[i]);
	if ((ft_strstr(print_num, "in") || (ft_strstr(print_num, "na"))) && 
	width > 0 && (precision >= 0 || flags[i--] == '.'))
		print_num = ft_strdup(print_num);	
	else
		print_num = ft_f_width(print_num, check_num, flags, width);
	return (print_num);
}

char	*manage_f_width_neg(char *print_num, char *flags, int width)
{
	int	len_printnum;

	len_printnum = 0;
	if (ft_iszero(flags) && !ft_strchr(flags, '+') &&
	!ft_strchr(flags, ' '))
		print_num = ft_strsub(print_num, 1, (int)ft_strlen(print_num));
	while (*print_num == ' ')
		print_num++;	
	print_num = ft_strjoin_free_s2("-", print_num);
	len_printnum = (int)ft_strlen(print_num);
	if (len_printnum < width)
	{
		while (len_printnum < width)
		{
			print_num = ft_strjoin_free_s2(" ", print_num);
			width--;
		}
	}
	return (print_num);
}

char	*ft_f_manager(char *print_num, long double check_num, char *flags,
int precision, int is_neg)
{
	int	width;
	int	i;

	i = 0;
	width = 0;
	if (ft_strchr("0+-. ", flags[i]))
		i++;
	if (ft_strchr(print_num, '-'))
		print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	if (ft_strcmp(print_num, "inf") != 0 && ft_strcmp(print_num, "-inf") != 0 &&
	ft_strcmp(print_num, "nan") != 0)
		print_num = ft_f_precision(print_num, precision, flags);
	if (check_num < 0)
			print_num = ft_strjoin_free_s2("-", print_num);
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]) || ft_iszero(flags))
		print_num = manage_f_width(print_num, check_num, flags, width, 
		precision, i);
	if (is_neg == 1 && !ft_strchr(print_num, '-'))
		print_num = manage_f_width_neg(print_num, flags, width);
	if (ft_strchr(flags, '+') && is_neg == 0)
		print_num = ft_strjoin_free_s2("+", print_num);
	if (ft_strchr(flags, ' ') && is_neg == 0 && !ft_strchr(flags, '+'))
		print_num = ft_strjoin_free_s2(" ", print_num);
	return (print_num);
}

int	ft_x_to_power_n (int precision)
{
    int	i;
    int	number;

	number = 1;
	i = 0;
	while (i < precision)
	{
		number *= 10;
		i++;
	}
	return (number);
}

int		ft_isnegative(double nbr)
{
	unsigned long long	*double_as_int;
	unsigned char		sign;

	double_as_int = (unsigned long long*)&nbr;
	sign = (unsigned char)(*double_as_int >> 63);
	return ((sign == 0) ? 0 : 1);
}

char	*ft_check_inf_nan(char *print_num, long double check_num, int precision)
{
	double			x;
	double			y;
	double			z;

	x = 1;
	y = 0;
	z = -1;
	if (check_num == x/y)
		print_num = ft_strdup("inf");
	else if (check_num == z/y)
		print_num = ft_strdup("-inf");
	else if (check_num != check_num)
		print_num = ft_strdup("nan");
	else
		print_num = ft_itoa_float(check_num, precision);
	return (print_num);
}

char	*ft_round_or_cut(char *print_num, long double check_num, int precision)
{
	long double		new_num;

	new_num = check_num * ft_x_to_power_n(precision);
	if (new_num - (int)new_num > 0.5 || new_num - (int)new_num < -0.5)
		check_num = ft_round(check_num, precision);
	else if (new_num - (int)new_num == 0.5 || new_num - (int)new_num == -0.5)
	{
		if (((int)new_num + 1) % 2 != 0)
			check_num = new_num / ft_x_to_power_n(precision);
		else
			check_num = ft_round(check_num, precision);
	}
	else
		check_num = ft_round(check_num, precision);
	print_num = ft_check_inf_nan(print_num, check_num, precision);
	return (print_num);
}

int	conv_f(va_list *ap, char *flags_collector)
{
	char			*print_num;
	long double		check_num;
	int				len;
	int				precision;
	int				is_neg;

	is_neg = 0;
	len = 0;
	print_num = NULL;
	if (ft_strchr(flags_collector, 'L'))
		check_num = va_arg(*ap, long double);
	else
		check_num = va_arg(*ap, double);
	is_neg = ft_isnegative(check_num);
	if (ft_strchr(flags_collector, '.'))
		precision = ft_atoi(ft_strchr(flags_collector, '.') + 1);
	else
		precision = 6;
	print_num = ft_round_or_cut(print_num, check_num, precision);
	print_num = ft_f_manager(print_num, check_num, flags_collector, precision, is_neg);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////PRINTF////////////////////////////////////////////////////////////////

int ft_printf(const char *format, ...)
{
	va_list	ap;
	int		char_counter;
	int		i;
	int		in_conversion;

	char_counter = 0;
	i = -1;
	in_conversion = 0;
	va_start(ap, format);
	while (format[++i])
		if (format[i] == '%' && !in_conversion)
		{
			in_conversion = 1;
			char_counter += conversion_solver(&format[i], &ap);
		}
		else if (!in_conversion)
		{
			ft_putchar(format[i]);
			char_counter++;
		}
		else if (is_conversion(format[i]))
			in_conversion = 0;
	va_end(ap);
	return (char_counter);
}
