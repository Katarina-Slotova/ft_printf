/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by katarinka         #+#    #+#             */
/*   Updated: 2022/03/11 14:45:20 by katarinka        ###   ########.fr       */
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
	/* if (conversion == 'c')
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
	if (conversion == 'f')
		return (conv_f(ap, flags_collector));
	if (conversion == '%')
		return (conv_percent());
	return (0); */
	return (conversion_identifier(conversion, flags_collector, ap));
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
	if (ft_strcmp(flags, "") != 0)
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
	if (ft_strchr(flags_collector, '.') || ft_strchr(flags_collector, ' '))
		ft_putstr("");
	else
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
		while(width > 0)
		{
			write(1, " ", 1);
			width--;
		}
	}
	else
	{
		while(width > 1)
		{
			write(1, " ", 1);
			width--;
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
	//printf("This is total len: %d\n", len);
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

////////////////////////////////////////////GENERAL FUNCTIONS////////////////////////////////////////////////////////////////

unsigned long long int	ft_oux_datatype(va_list *ap, char *flags)
{
	if (ft_strstr(flags, "hh"))
		return (unsigned char)va_arg(*ap, unsigned long long int);
	else if (ft_strchr(flags, 'h'))
		return (unsigned short int)va_arg(*ap, unsigned long long int);
	else if (ft_strchr(flags, 'l'))
		return (unsigned long int)va_arg(*ap, unsigned long long int);
	else if (ft_strstr(flags, "ll"))
		return va_arg(*ap, unsigned long long int);
	else
		return (unsigned int)va_arg(*ap, unsigned long long int);
}

long long int	ft_di_datatype(va_list *ap, char *flags)
{
	if (ft_strstr(flags, "hh"))
		return (signed char)va_arg(*ap, long long int);
	else if (ft_strchr(flags, 'h'))
		return (short int)va_arg(*ap, long long int);
	else if (ft_strchr(flags, 'l'))
		return (long int)va_arg(*ap, long long int);
	else if (ft_strstr(flags, "ll"))
		return va_arg(*ap, long long int);
	else
		return (int)va_arg(*ap, unsigned long long int);
}

int	ft_iszero(char *flags)
{
	int	i;
	int index_zero;
	int	index_comp;

	i = 0;
	index_zero = -1;
	index_comp = -1;
	while (flags[i])
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

char	*dio_width_emptyspaces(int empty_spaces, char *flags, char *final_num)
{
	while (empty_spaces-- > 0)
	{
		if (ft_iszero(flags))
			final_num = ft_strjoin(final_num, "0");
		else 
			final_num = ft_strjoin(final_num, " ");
	}
	return (final_num);
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
			final_num = ft_strjoin(final_num, print_num);
			while (empty_spaces-- > 0)
				final_num = ft_strjoin(final_num, " ");
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
			final_num = ft_strjoin(final_num, print_num);
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

	if ((int)ft_strlen(print_num) < precision)
	{
		final_num = ft_strnew(precision);
		zeroed_spaces = precision - ft_strlen(print_num);
		while (zeroed_spaces-- > 0)
			final_num = ft_strjoin("0", final_num);
		final_num = ft_strjoin(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
	return (final_num);	
}

/* char	*ft_o_manager(char *print_num, int check_num, char *flags)
{
	int	width;
	int	precision;
	int	i;

	i = 0;
	precision = 0;
	width = 0;
	printf("These are the flags: <<%s>>.\n", flags);
	if (ft_strchr("#-.", flags[i]))
		i++;
	printf("here: %d\n", i);
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		print_num = ft_u_precision(print_num, flags, precision);
	}
	else if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
	{
		width = ft_atoi(&flags[i]);
		if (width < 0)
			width = width * -1;
		print_num = ft_u_width(print_num, check_num, flags, width);
	}
	return (print_num);
} */

char	*ft_hashtag(char *print_num, int check_num, char *flags, int w_or_p)
{
	char	*final_num;
	int		i;

	i = 0;
	if (print_num[0] == '\0' || print_num[0] == '0')
		final_num = ft_strdup("0");
	if (ft_strchr(flags, '.'))
	{
		final_num = ft_o_precision(print_num, w_or_p);
		final_num = ft_strjoin("0", final_num);
	}
	else if (ft_strchr(flags, '-') || ft_strchr(flags, ft_isdigit(*flags)))
	{
		if (check_num != 0)
		{
			final_num = ft_strjoin("0", print_num);
			final_num = ft_o_width(final_num, flags, w_or_p);
		}
		//final_num = ft_o_width(final_num, flags, w_or_p);
	}
	else
		final_num = ft_strjoin("0", print_num);
	free (print_num);
	return (final_num);
}

char	*ft_o_manager(char *print_num, int check_num, char *flags) //SHORTEN - extra 6 lines
{
	int	width;
	int	precision;
	int	i;

	i = 0;
	precision = 0;
	width = 0;
	//printf("The flag is <<%s>>\n", flags);
	if (ft_strchr("0-#.", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		if (ft_strchr(flags, '#'))
			print_num = ft_hashtag(print_num, check_num, flags, precision);
		else
			print_num = ft_o_precision(print_num, precision);
	}
	if (ft_strchr(flags, '-') || ft_isdigit(*flags) || ft_strchr(flags, '#'))
	{
 		while (ft_isdigit(flags[i]) != 1)
			i++;
		width = ft_atoi(&flags[i]);
		if (width < 0)
			width *= -1;
	 	if (ft_strchr(flags, '#'))
			print_num = ft_hashtag(print_num, check_num, flags, width);
		else
			print_num = ft_o_width(print_num, flags, width);
	}
/* 	else if (ft_strchr(flags, '#'))
		print_num = ft_strjoin("0", print_num); */
	return (print_num);
}

int	conv_o(va_list *ap, char *flags_collector)
{
	char	*print_num;
	int		check_num;
	int		len;

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
	else if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
	{
		width = ft_atoi(&flags[i]);
		if (width < 0)
			width = width * -1;
		print_num = ft_o_width(print_num, flags, width);
	}
	return (print_num);
}

int	conv_u(va_list *ap, char *flags_collector)
{
	char	*print_num;
	int		check_num;
	int		len;

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

/* char	*ft_hashtag_x(char *print_num, int check_num, char *flags, int w_or_p)
{
	char	*final_num;
	int		i;

	i = 0;
	if (print_num[0] == '\0' || print_num[0] == '0')
		final_num = ft_strdup("0");
	if (ft_strchr(flags, '.'))
	{
		final_num = ft_o_precision(print_num, w_or_p);
		final_num = ft_strjoin("0x", final_num);
	}
	else if (ft_strchr(flags, '-') || ft_strchr(flags, ft_isdigit(*flags)))
	{
		if (check_num != 0)
		{
			final_num = ft_strjoin("0x", print_num);
			final_num = ft_o_width(final_num, flags, w_or_p);
		}
		final_num = ft_o_width(final_num, flags, w_or_p);
	}
	else
		final_num = ft_strjoin("0x", print_num);
	free (print_num);
	return (final_num);
} */

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
		final_num = ft_strjoin("0X", final_num);
	}
	else if (ft_strchr(flags, '-') || ft_strchr(flags, ft_isdigit(*flags)))
	{
		if (ft_strchr(flags, '0') && !ft_strchr(flags, '-'))
		{
			print_num = ft_o_width(print_num, flags, w_or_p);
			print_num = ft_strsub(print_num, 2, ft_strlen(print_num));
		}
		if (conversion == 'x')
			final_num = ft_strjoin("0x", print_num);
		else if (conversion == 'X')
			final_num = ft_strjoin("0X", print_num);
		final_num = ft_o_width(final_num, flags, w_or_p);
	}
	else
	{
		if (conversion == 'x')
			final_num = ft_strjoin("0x", print_num);
		else if (conversion == 'X')
			final_num = ft_strjoin("0X", print_num);
	}
	free(print_num);
	return (final_num);
}

char	*ft_x_manager(char *print_num, int check_num, char *flags, char conversion) // SHORTEN - 5 extra lines
{
	int		width;
	int		precision;
	int		i;
	char	*original_printnum;

	i = 0;
	precision = 0;
	width = 0;
	original_printnum = print_num;
	if (ft_strchr("#-.", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		print_num = ft_o_precision(print_num, precision);
		if (ft_strchr(flags, '#') && check_num != 0 && conversion == 'x')
			print_num = ft_strjoin("0x", print_num);
		else if (ft_strchr(flags, '#') && check_num != 0 && conversion == 'X')
			print_num = ft_strjoin("0X", print_num);
	}
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]))
	{
		if (ft_isdigit(flags[i]) != 1)
			i++;
		width = ft_atoi(&flags[i]);
		if (ft_strchr(flags, '#') && check_num != 0)
			print_num = ft_hashtag_x(print_num, conversion, flags, width);
		else
			print_num = ft_o_width(print_num, flags, width);
	}
	else if (ft_strchr(flags, '#') && check_num != 0)
	{
		if (conversion == 'x')
			print_num = ft_strjoin("0x", print_num);
		else if (conversion == 'X')
			print_num = ft_strjoin("0X", print_num);
	}
	return (print_num);
}

int	conv_x(va_list *ap, char *flags_collector, char conversion)
{
	char	*print_num;
	unsigned long long int		check_num;
	int		len;

/* 	if (flags_collector)
		printf("<<<%s>>>", flags_collector); */
	len = 0;
	check_num = ft_oux_datatype(ap, flags_collector);
	print_num = ft_itoa_hex(check_num, 16, conversion);
	print_num = ft_x_manager(print_num, check_num, flags_collector, conversion);
	//printf("This is print num: %s\n", print_num);
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
	if (num < 0 || num == 0)
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

	//printf("This is dibased num: %ld\n", num);
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

char	*di_width_flags(char *flags, int check_num, int width, char *final_num)
{
	if (ft_strchr(flags, '+') && !ft_strchr(flags, '0') 
	&& check_num >= 0)
	{
		final_num = ft_strsub(final_num, 1, width);
		final_num = ft_strjoin(final_num, "+");
	}
	else if ((ft_strchr(flags, '+') || ft_strchr(flags, ' ')) 
	&& ft_strchr(flags, '0') && check_num >= 0)
	{
		final_num = ft_strsub(final_num, 1, width);
		if (ft_strchr(flags, '+'))
			final_num = ft_strjoin("+", final_num);
		else if (ft_strchr(flags, ' '))
			final_num = ft_strjoin(" ", final_num);
	}
	return (final_num);
}

char	*ft_di_width(char *print_num, int check_num, char *flags, int width) // SHORTEN - 6 extra lines
{
	char	*final_num;
	int		empty_spaces;

	if ((int)ft_strlen(print_num) < width)
	{
		empty_spaces = width - (int)ft_strlen(print_num);
		final_num = ft_strnew(width);
		if (ft_strchr(flags, '-'))
		{
			final_num = ft_strcpy(final_num, print_num);
			if (ft_strchr(flags, '+'))
				final_num = ft_strjoin("+", final_num);
			while (empty_spaces-- > 0)
				final_num = ft_strjoin(final_num, " ");
		}
		else
		{
			if (check_num < 0 && (ft_strchr(flags, '0') || ft_strchr(flags, '+')))
			{
				//printf("This is print num: %s\n", final_num);
				final_num = ft_strjoin("-", final_num);
				print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
			}
			final_num = dio_width_emptyspaces(empty_spaces, flags, final_num);
			final_num = di_width_flags(flags, check_num, width, final_num);
			/* 	while (empty_spaces-- > 0)
			{
				if (ft_iszero(flags))
					final_num = ft_strjoin(final_num, "0");
				else
					final_num = ft_strjoin(final_num, " ");
			} */
			/* 	if (ft_strchr(flags, '+') && !ft_strchr(flags, '0') 
			&& check_num >= 0)
			{
				final_num = ft_strsub(final_num, 1, width);
				final_num = ft_strjoin(final_num, "+");
			}
			else if ((ft_strchr(flags, '+') || ft_strchr(flags, ' ')) 
			&& ft_strchr(flags, '0') && check_num >= 0)
			{
				final_num = ft_strsub(final_num, 1, width);
				if (ft_strchr(flags, '+'))
					final_num = ft_strjoin("+", final_num);
				else if (ft_strchr(flags, ' '))
					final_num = ft_strjoin(" ", final_num);
			} */
			final_num = ft_strjoin(final_num, print_num);
		}
	}
	else
		final_num = ft_strdup(print_num);
	free(print_num);
	return (final_num);
}

char	*ft_di_plus_flag(char *print_num)
{
	print_num = ft_strjoin("+", print_num);
	return (print_num);
}

char	*ft_di_space_flag(char *print_num)
{
	print_num = ft_strjoin(" ", print_num);
	return (print_num);
}

char	*ft_di_precision(char *print_num, char *flags, int precision, int check_num)
{
	char	*final_num;
	int		zeroed_spaces;

	if ((int)ft_strlen(print_num) < precision)
	{
		final_num = ft_strnew(precision);
		zeroed_spaces = precision - ft_strlen(print_num);
		while (zeroed_spaces > 0)
		{
			final_num = ft_strjoin("0", final_num);
			zeroed_spaces--;
		}
		final_num = ft_strjoin(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
	if (ft_strchr(flags, '+') && check_num >= 0)
		final_num = ft_strjoin("+", final_num);
	if (ft_strchr(flags, ' ') && !ft_strchr(flags, '+') && check_num >= 0)
		final_num = ft_di_space_flag(final_num);
	return (final_num);	
}

char	*ft_di_manager(char *print_num, int check_num, char *flags)
{
	int	width;
	int	precision;
	int	i;

	i = 0;
	precision = 0;
	width = 0;
	if (ft_strchr("0+-. ", flags[i]))
		i++;
	if (ft_strchr(flags, '.'))
	{
		precision = ft_atoi(ft_strchr(flags, '.') + 1);
		print_num = ft_di_precision(print_num, flags, precision, check_num);
	}
	if (ft_strchr(flags, '-') || ft_isdigit(flags[i]) ||
	ft_strchr(flags, '0'))
	{
		if (ft_isdigit(flags[i]) != 1)
			i++;
		width = ft_atoi(&flags[i]);
		print_num = ft_di_width(print_num, check_num, flags, width);
	}
	else if (ft_strchr(flags, '+') && check_num >= 0)
		print_num = ft_di_plus_flag(print_num);
	else if (ft_strchr(flags, ' ') && check_num >= 0)
		print_num = ft_di_space_flag(print_num);
	return (print_num);
}

int	conv_d_i(va_list *ap, char *flags_collector)
{
	char	*print_num;
	int		check_num;
	int		len;

 /* 	if (flags_collector)
		printf("<<%s>>", flags_collector); */
	len = 0;
	check_num = ft_di_datatype(ap, flags_collector);
	print_num = ft_itoa_dibase(check_num, 10);
	print_num = ft_di_manager(print_num, check_num, flags_collector);
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
	//printf("This is string num: %s\n", string_num);
	while (precision > 0)
	{
		rounder = rounder / 10;
		precision--;
	}
	//printf("This is original num: %Lf\n", check_num);
	if (check_num >= 0)
		rounded_num = check_num + rounder;
	else
		rounded_num = check_num - rounder;
	//printf("<<%Lf>>\n", rounded_num);
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
	//printf("<<<%Lf>>>", check_num);
	before_point = ft_itoa_dibase(num, 10);
/* 	if (before_point[0] == '0' && check_num == -0.)
		before_point = ft_strjoin("-", before_point); */
	after_point = ft_float_convertor(check_num, num, precision);
	final_str = ft_strjoin(before_point, after_point);
	//printf("%s\n", final_str);
	free(before_point);
	free(after_point);
	return (final_str);
}

int	conv_f(va_list *ap, char *flags_collector)
{
	char			*print_num;
	long double		check_num;
	//long double				original_num;
	int				len;
	int				precision;

	len = 0;
/* 	if (flags_collector)
		printf("%s", flags_collector); */
	if (ft_strchr(flags_collector, '.'))
		precision = ft_atoi(ft_strchr(flags_collector, '.') + 1);
	else
		precision = 6;
	if (ft_strchr(flags_collector, 'L'))
		check_num = va_arg(*ap, long double);
	else
		check_num = va_arg(*ap, double);
	//original_num = check_num;
	//printf("This is the original number: %Lf\n", original_num);
	check_num = ft_round(check_num, precision);
	//printf("^^%Lf^^\n", check_num);
	print_num = ft_itoa_float(check_num, precision);
	print_num = ft_cut_leftover(print_num, precision);
	/* if (original_num == -0)
		print_num = ft_strjoin("-", print_num); */
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
