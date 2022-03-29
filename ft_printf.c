/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 17:32:58 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h> // REMOVE THIS LINE

int	is_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
	|| c == 'u' || c == 'x' || c == 'X' || c == 'f' || c == '%')
		return (1);
	else
		return (0);
}

int	is_flag(char c)
{
	if (c == 'h' || c == 'l' || c == 'L' || c == '#' || c == '-' || c == '+'
	|| c == '0' || c == '.' || c == ' ' || ft_isdigit(c))
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
	utils->flags = ft_strnew(20);
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

////////////////////////////////////////////GENERAL FUNCTIONS////////////////////////////////////////////////////////////////

unsigned long long int	ft_oux_datatype(va_list *ap, t_specs *utils)
{
	if (ft_strstr(utils->flags, "hh"))
		return (unsigned char)va_arg(*ap, unsigned int);
	else if (ft_strchr(utils->flags, 'h'))
		return (unsigned short int)va_arg(*ap, unsigned int);
	else if (ft_strchr(utils->flags, 'l'))
		return va_arg(*ap, unsigned long int);
	else if (ft_strstr(utils->flags, "ll"))
		return va_arg(*ap, unsigned long long int);
	else
		return va_arg(*ap, unsigned int);
}

long long int	ft_di_datatype(va_list *ap, t_specs *utils)
{
	if (ft_strstr(utils->flags, "hh"))
		return (signed char)va_arg(*ap, int);
	else if (ft_strchr(utils->flags, 'h'))
		return (short int)va_arg(*ap, int);
	else if (ft_strchr(utils->flags, 'l'))
		return va_arg(*ap, long int);
	else if (ft_strstr(utils->flags, "ll"))
		return va_arg(*ap, long long int);
	else
		return va_arg(*ap, int);
}

long double	ft_f_datatype(va_list *ap, t_specs *utils)
{
	if (ft_strchr(utils->flags, 'L'))
		return va_arg(*ap, long double);
	else
		return va_arg(*ap, double);
}

int	ft_iszero(t_specs *utils)
{
	int	i;
	int index_zero;
	int	index_comp;

	i = 0;
	index_zero = -1;
	index_comp = -1;
	while (utils->flags[i] && utils->flags[i] != '.')
	{
		if (utils->flags[i] == '0')
			index_zero = i;
		if (utils->flags[i] >= '1' && utils->flags[i] <= '9')
			index_comp = i;
		if ((index_zero < index_comp) && index_zero != -1)
			return (1);
		i++;
	}
	return (0);
}

char	*dio_width_emptyspaces(t_specs *utils, char *final_num)
{
	if (utils->empty_spaces > 0)
	{
		while (utils->empty_spaces-- > 0)
		{
			if (ft_iszero(utils) && !ft_strchr(utils->flags, '.'))
				final_num = ft_strjoin_free_s2("0", final_num);
			else 
				final_num = ft_strjoin_free_s1(final_num, " ");
		}
	}
	return (final_num);
}

////////////////////////////////////////////CONV_C////////////////////////////////////////////////////////////////

void	ft_handle_minus(char c, t_specs *utils)
{
	ft_putchar(c);
	utils->width--;
	while(utils->width > 0)
	{
		ft_putchar(' ');
		utils->width--;
	}
}

int	ft_char_width(char c, t_specs *utils)
{
	int	total_width;

	total_width = utils->width;
	if (ft_strchr(utils->flags, '-'))
		ft_handle_minus(c, utils);
	else
	{
		while(utils->width > 1)
		{
			ft_putchar(' ');
			utils->width--;
		}
		ft_putchar(c);
	}
	return (total_width);
}

int	ft_char_manager(char c, t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strcmp(utils->flags, "") != 0)
	{
		if (ft_strchr("-", utils->flags[i]))
			i++;
		if (ft_isdigit(utils->flags[i]))
			utils->width = ft_atoi(utils->flags + i);
		else
		{
			ft_putchar(c);
			return (1);
		}
		return (ft_char_width(c, utils));
	}
	else
	{
		ft_putchar(c);
		return (1);
	}
}

int	conv_c(va_list *ap, t_specs *utils)
{
	char	c;
	int		len;
	
	len = 0;
	c = va_arg(*ap, int);
	len = ft_char_manager(c, utils);
	return (len);
}

////////////////////////////////////////////CONV_%////////////////////////////////////////////////////////////////

int	ft_percent_width(t_specs *utils)
{
	int	total_width;

	total_width = utils->width;
	if (ft_strchr(utils->flags, '-'))
	{
		write(1, "%", 1);
		utils->width--;
		while(utils->width-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while(utils->width-- > 1)
		{
			if (ft_strchr(utils->flags, '0'))
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
		write(1, "%", 1);
	}
	return (total_width);
}

int	ft_percent_manager(t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i]))
	{
		if (ft_strchr("-", utils->flags[i]))
			i++;
		if (ft_isdigit(utils->flags[i]))
			utils->width = ft_atoi(utils->flags + i);
		return (ft_percent_width(utils));
	}
	else
	{
		write(1, "%", 1);
		return (1);
	}
}

int	conv_percent(t_specs *utils)
{
	int		len;

	len = 0;
	len = ft_percent_manager(utils);
	return (len);
}
////////////////////////////////////////////CONV_S////////////////////////////////////////////////////////////////

char	*ft_str_width_minus(char *str, char *final_str, t_specs *utils)
{
	if (ft_strchr(utils->flags, '-'))
	{
		final_str = ft_strcpy(final_str, str);
		while (utils->empty_spaces > 0)
		{
			final_str = ft_strjoin_free_s1(final_str, " ");
			utils->empty_spaces--;
		}
	}
	else
	{
		while (utils->empty_spaces > 0)
		{
			final_str = ft_strjoin_free_s1(final_str, " ");
			utils->empty_spaces--;
		}
		final_str = ft_strjoin_free_s1(final_str, str);
	}
	return (final_str);
}

char	*ft_str_width(char *str, t_specs *utils)
{
	char	*final_str;
	int		i;

	i = 0;
	if ((int)ft_strlen(str) < utils->width)
	{
		final_str = ft_strnew(utils->width);
		utils->empty_spaces = utils->width - ft_strlen(str);
		final_str = ft_str_width_minus(str, final_str, utils);
	}
	else
		final_str = ft_strdup(str);
	free(str);
	return (final_str);
}

char	*ft_str_precision(char *str, t_specs *utils)
{
	char	*final_str;
	
	if ((int)ft_strlen(str) > utils->precision)
		final_str = ft_strsub(str, 0, utils->precision);
	else
		final_str = ft_strdup(str);
	free(str);
	return (final_str);
}

char	*ft_str_manager(char *str, t_specs *utils)
{
	int	i;

	i = 0;
	if (utils->flags)
	{
		if (ft_strchr(utils->flags, '.'))
		{
			utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
			str = ft_str_precision(str, utils);
		}
		if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i]))
		{
			utils->width = ft_atoi(&utils->flags[i]);
			if (utils->width < 0)
				utils->width *= -1;
			str = ft_str_width(str, utils);
		}
	}
	return (str);
}

int	conv_s(va_list *ap, t_specs *utils)
{
	char	*check_str;
	char	*print_str;
	int		len;
	
	check_str = va_arg(*ap, char*);
	if (check_str == NULL)
		print_str = ft_strdup("(null)");
	else
		print_str = ft_strdup(check_str);
	print_str = ft_str_manager(print_str, utils);
	ft_putstr(print_str);
	len = ft_strlen(print_str);
	free(print_str);
	return(len);
}

////////////////////////////////////////////CONV_O////////////////////////////////////////////////////////////////

char	*ft_o_width(char *print_num, t_specs *utils)
{
	char	*final_num;

	if ((int)ft_strlen(print_num) < utils->width)
	{
		utils->empty_spaces = utils->width - (int)ft_strlen(print_num);
		final_num = ft_strnew(utils->width);
		if (ft_strchr(utils->flags, '-'))
		{
			final_num = ft_strjoin_free_s1(final_num, print_num);
			while (utils->empty_spaces-- > 0)
				final_num = ft_strjoin_free_s1(final_num, " ");
		}
		else
		{
			final_num = dio_width_emptyspaces(utils, final_num);
			final_num = ft_strjoin_free_s1(final_num, print_num);
		}
	}
	else
		final_num = ft_strdup(print_num);
	free(print_num);
	return (final_num);
}

char	*ft_o_precision(char *print_num, t_specs *utils)
{
	char	*final_num;
	int		zeroed_spaces;

	if (ft_strcmp(print_num, "0") == 0 && utils->precision == 0)
		final_num = ft_strnew(1);
	else if ((int)ft_strlen(print_num) < utils->precision)
	{
		final_num = ft_strnew(utils->precision);
		zeroed_spaces = utils->precision - ft_strlen(print_num);
		while (zeroed_spaces-- > 0)
			final_num = ft_strjoin_free_s2("0", final_num);
		final_num = ft_strjoin_free_s2(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
	return (final_num);
}

char	*ft_manage_o_width(char *print_num, unsigned long long check_num, 
int i, t_specs *utils)
{
	while (utils->flags[i] && ft_isdigit(utils->flags[i]) != 1 &&
	!ft_strchr(utils->flags, 'h'))
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	if (utils->width < 0)
		utils->width *= -1;
	if (ft_strchr(utils->flags, '#') && !ft_strchr(utils->flags, '.') &&
	check_num != 0)
		print_num = ft_strjoin_free_s2("0", print_num);
	print_num = ft_o_width(print_num, utils);
	return (print_num);
}

char	*ft_o_manager(char *print_num, unsigned long long check_num,
t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr("0-#.", utils->flags[i]))
		i++;
	if (ft_strchr(utils->flags, '.'))
	{
		utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
		if ((print_num[0] == '\0' || print_num[0] == '0') &&
		ft_strchr(utils->flags, '#') && utils->precision == 0)
			print_num = ft_strdup("0");
		else 
		{
			if (ft_strchr(utils->flags, '#'))
				print_num = ft_strjoin_free_s2("0", print_num);
			print_num = ft_o_precision(print_num, utils);
		}
	}
	if (ft_strchr(utils->flags, '-') || ft_isdigit(*utils->flags) ||
	ft_strchr(utils->flags, '#'))
		print_num = ft_manage_o_width(print_num, check_num, i, utils);
	return (print_num);
}

int	conv_o(va_list *ap, t_specs *utils)
{
	char						*print_num;
	unsigned long long int		check_num;
	int							len;

	len = 0;
	check_num = ft_oux_datatype(ap, utils);
	print_num = ft_itoa_base_u(check_num, 8);
	print_num = ft_o_manager(print_num, check_num, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////CONV_U////////////////////////////////////////////////////////////////

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
		while (utils->flags[i] && (utils->flags[i] == '0' ||
		ft_isdigit(utils->flags[i]) != 1))
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

////////////////////////////////////////////CONV_x_X////////////////////////////////////////////////////////////////

char	*ft_itoa_hex(uintmax_t num, int base, t_specs *utils)
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
		str[i--] = ft_base_hex(num, base, utils->c);
		num = num / base;
	}
	if (num <= 9)
		str[i--] = ft_base_hex(num, base, utils->c);
	else
		str[i--] = ft_base_hex(num, base, utils->c);
	return (str);
}

char	*ft_hashtag_width_x(char *print_num, char *final_num, t_specs *utils)
{
	if (ft_iszero(utils) && !ft_strchr(utils->flags, '-'))
	{
		print_num = ft_o_width(print_num, utils);
		print_num = ft_strsub(print_num, 2, ft_strlen(print_num));
	}
	if (utils->c == 'x')
		final_num = ft_strjoin_free_s2("0x", print_num);
	else if (utils->c == 'X')
		final_num = ft_strjoin_free_s2("0X", print_num);
	final_num = ft_o_width(final_num, utils);
	return (final_num);
}

char	*ft_hashtag_x(char *print_num, t_specs *utils)
{
	char	*final_num;
	int		i;

	i = 0;
	if (print_num[0] == '\0' || print_num[0] == '0')
		final_num = ft_strdup("0");
	if (ft_strchr(utils->flags, '.'))
	{
		final_num = ft_o_precision(print_num, utils);
		if (utils->c == 'x')
			final_num = ft_strjoin_free_s2("0x", print_num);
		else if (utils->c == 'X')
			final_num = ft_strjoin_free_s2("0X", print_num);
	}
	if (ft_strchr(utils->flags, '-') ||
	ft_strchr(utils->flags, ft_isdigit(*utils->flags)))
		final_num = ft_hashtag_width_x(print_num, final_num, utils);
	else
		if (utils->c == 'x')
			final_num = ft_strjoin_free_s2("0x", print_num);
		else if (utils->c == 'X')
			final_num = ft_strjoin_free_s2("0X", print_num);
	return (final_num);
}

char	*ft_manage_x_width(char *print_num, unsigned long long check_num,
t_specs *utils, int i)
{
	while (utils->flags[i] && (utils->flags[i] == '0' ||
	ft_isdigit(utils->flags[i]) != 1))
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	if (ft_strchr(utils->flags, '#') && check_num != 0 &&
	!ft_strchr(utils->flags, '.'))
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
	else if (ft_strchr(utils->flags, '#') && check_num != 0 &&
	utils->c == 'X')
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
	else if (ft_strchr(utils->flags, '#') && check_num != 0 &&
	!ft_strchr(utils->flags, '.'))
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
	char						*print_num;
	unsigned long long int		check_num;
	int							len;

	len = 0;
	check_num = ft_oux_datatype(ap, utils);
	print_num = ft_itoa_hex(check_num, 16, utils);
	print_num = ft_x_manager(print_num, check_num, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);	
	return (len);
}

////////////////////////////////////////////CONV_P////////////////////////////////////////////////////////////////

char	*ft_manage_ptr_emptyspcs(char *final_str, t_specs *utils)
{
	while (utils->empty_spaces > 0)
	{
		final_str = ft_strjoin_free_s2(" ", final_str);
		utils->empty_spaces--;
	}
	return (final_str);
}

char	*ft_ptr_width(char *ptr, t_specs *utils)
{
	char	*final_str;

	if ((int)ft_strlen(ptr) < utils->width)
	{
		final_str = ft_strnew(utils->width);
		utils->empty_spaces = utils->width - (int)ft_strlen(ptr);
		if (ft_strchr(utils->flags, '-'))
		{
			final_str = ft_manage_ptr_emptyspcs(final_str, utils);
			final_str = ft_strjoin_free_s2(ptr, final_str);
		}
		else
		{
			final_str = ft_strcpy(final_str, ptr);
			final_str = ft_manage_ptr_emptyspcs(final_str, utils);
		}
	}
	else
		final_str = ft_strdup(ptr);
	free(ptr);
	return (final_str);
}

char	*ft_ptr_precision(char *ptr, t_specs *utils)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = ft_strnew(utils->precision);
	if (ft_strequ(ptr, "0x0") && utils->precision == 0)
	{
		free(ptr);
		return (ft_strdup("0x"));
	}
	else if ((int)ft_strlen(ptr) < utils->precision)
	{
		while (utils->empty_spaces > 0)
		{
			final_str = ft_strjoin_free_s2("0", final_str);
			utils->empty_spaces--;
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

char	*ft_ptr_manager(char *ptr, t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr("-.", utils->flags[i]))
		i++;
	if (ft_strchr(utils->flags, '.'))
	{
		utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
		utils->empty_spaces = utils->precision - (int)ft_strlen(ptr) + 2;
		ptr = ft_ptr_precision(ptr, utils);
	}
	if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i]))
	{
		utils->width = ft_atoi(utils->flags + i);
		ptr = ft_ptr_width(ptr, utils);
	}
	return (ptr);
}

int	conv_p(va_list *ap, t_specs *utils)
{
	void	*ptr;
	char	*final_ptr;
	int		len;
	
	ptr = va_arg(*ap, void*);
	final_ptr = ft_itoa_hex((uintptr_t)ptr, 16, utils);
	final_ptr = ft_strjoin_free_s2("0x", final_ptr);
		final_ptr = ft_ptr_manager(final_ptr, utils);
	ft_putstr(final_ptr);
	len = ft_strlen(final_ptr);
	free(final_ptr);
	return(len);
}

////////////////////////////////////////////CONV_D_I////////////////////////////////////////////////////////////////

char	*di_width_flags(char *final_num, long long int check_num,
t_specs *utils)
{
	char	*final_num2;

	final_num2 = NULL;
	if (ft_strchr(utils->flags, '+') && !ft_iszero(utils) &&
	!ft_strchr(utils->flags, '.')
	&& check_num >= 0)
	{
		final_num = ft_strsub(final_num, 1, utils->width);
		final_num2 = ft_strjoin_free_s2("+", final_num);
	}
	else if ((ft_strchr(utils->flags, '+') || ft_strchr(utils->flags, ' ')) &&
	!ft_strchr(utils->flags, '.') && ft_iszero(utils) && check_num >= 0)
	{
		final_num = ft_strsub(final_num, 1, utils->width);
		if (ft_strchr(utils->flags, '+'))
			final_num2 = ft_strjoin_free_s2("+", final_num);
		else if (ft_strchr(utils->flags, ' '))
			final_num2 = ft_strjoin_free_s2(" ", final_num);
		}
	else
	{
		final_num2 = ft_strdup(final_num);
		free(final_num);
	}
	return (final_num2);
}

char	*di_width_minusflag(char *final_num, char *print_num,
long long int check_num, t_specs *utils)
{
	final_num = ft_strcpy(final_num, print_num);
	if (ft_strchr(utils->flags, '+') && !ft_strchr(utils->flags, '.'))
	{
		final_num = ft_strjoin_free_s2("+", final_num);
		utils->empty_spaces--;
	}
	if (ft_strchr(utils->flags, ' ') && !ft_strchr(utils->flags, '.') &&
	check_num >= 0)
	{
		final_num = ft_strjoin_free_s2(" ", final_num);
		utils->empty_spaces--;
	}
	while (utils->empty_spaces-- > 0)
		final_num = ft_strjoin_free_s1(final_num, " ");
	return (final_num);
}

char	*ft_di_negative_num(char *final_num, char *print_num,
long long int check_num, t_specs *utils)
{
 	char	*final_num2;

	final_num = dio_width_emptyspaces(utils, final_num);
	final_num2 = di_width_flags(final_num, check_num, utils);
	if (check_num < 0 && ft_strchr(utils->flags, '.'))
		final_num2 = ft_strjoin_free_s1(final_num2, "-");
	else
		final_num2 = ft_strjoin_free_s2("-", final_num2);
	print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	final_num2 = ft_strjoin_free_s2(final_num2, print_num);
	return (final_num2);
}

char	*di_width_above_numlen(char *final_num, char *print_num,
long long int check_num, t_specs *utils)
{
	if (ft_strchr(utils->flags, '-'))
		final_num = di_width_minusflag(final_num, print_num, check_num,
		utils);
	else if ((ft_iszero(utils) || ft_strchr(utils->flags, '+')) &&
	check_num < 0)
		final_num = ft_di_negative_num(final_num, print_num, check_num,
		utils);
	else
	{
		final_num = dio_width_emptyspaces(utils, final_num);
		final_num = di_width_flags(final_num, check_num, utils);
		final_num = ft_strjoin_free_s1(final_num, print_num);
	}
	return (final_num);
}

char	*ft_di_width(char *print_num, long long int check_num, t_specs *utils)
{
	char	*final_num;
	int		checker;

	checker = 0;
	if ((int)ft_strlen(print_num) <= utils->width)
	{
		checker = 1;
		utils->empty_spaces = utils->width - (int)ft_strlen(print_num);
		final_num = ft_strnew(utils->width);
		final_num = di_width_above_numlen(final_num, print_num, check_num,
		utils);
	}
	else
		final_num = ft_strdup(print_num);
	if (ft_strchr(utils->flags, ' ') && !ft_strchr(utils->flags, '.') &&
	check_num >= 0 && checker == 0)
		final_num = ft_strjoin_free_s2(" ", final_num);
	free(print_num);
	return (final_num);
}

char	*ft_di_precision(char *print_num, long long int check_num,
t_specs *utils)
{
	char	*final_num;
	int		zeroed_spaces;

	if (ft_strcmp(print_num, "0") == 0 && utils->precision == 0)
		final_num = ft_strnew(1);
	else if ((int)ft_strlen(print_num) < utils->precision)
	{
		final_num = ft_strnew(utils->precision);
		zeroed_spaces = utils->precision - ft_strlen(print_num);
		while (zeroed_spaces > 0)
		{
			final_num = ft_strjoin_free_s2("0", final_num);
			zeroed_spaces--;
		}
		final_num = ft_strjoin_free_s1(final_num, print_num);
	}
	else
		final_num = ft_strdup(print_num);
	if (ft_strchr(utils->flags, '+') && check_num >= 0)
		final_num = ft_strjoin_free_s2("+", final_num);
	if (ft_strchr(utils->flags, ' ') && !ft_strchr(utils->flags, '+') &&
	check_num >= 0)
		final_num = ft_strjoin_free_s2(" ", final_num);
	return (final_num);
}

char	*di_prec_not_zero(char *print_num, long long int check_num,
t_specs *utils)
{
	int		i;
	int		diff;
	char	*print_num2;

	diff = 0;
	i = 0;
	diff = utils->width - utils->precision;
	print_num2 = ft_strsub(print_num, diff, ft_strlen(print_num));
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
t_specs *utils)
{
	int	i;

	if ((utils->precision < utils->width) && ft_strchr(utils->flags, '.') &&
	!ft_strchr(utils->flags, '+') 
	&& !ft_strchr(utils->flags, '-') &&
	(int)ft_numlen_base(check_num, 10) < utils->precision)
		print_num = di_prec_not_zero(print_num, check_num, utils);
	else if (utils->precision == 0 && utils->width > utils->precision &&
	ft_strchr(utils->flags, '.'))
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
	if (ft_strchr(utils->flags, '-') || (ft_isdigit(utils->flags[i]) &&
	utils->flags[0] != '.') || ft_iszero(utils))
		print_num = di_manage_width(print_num, check_num, i, utils);
	if (ft_strchr(utils->flags, '+') && check_num >= 0 &&
	!ft_strchr(print_num, '+'))
		print_num = ft_strjoin_free_s2("+", print_num);
	else if (ft_strchr(utils->flags, ' ') && check_num >= 0 &&
	!ft_strchr(print_num, ' '))
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

////////////////////////////////////////////CONV_F////////////////////////////////////////////////////////////////

char	*ft_cut_leftover(char *str, t_specs *utils)
{
	int		i;
	int		len;
	char	*final_str;

	i = 0;
	while (str[i] != '.')
		i++;
	len = i + utils->precision + 1;
 	if (utils->precision == 0 && !ft_strchr(utils->flags, '#'))
		len--;
	while (str[i] && i < len)
		i++;
	final_str = ft_strsub(str, 0, i);
	free(str);
	return (final_str);
}

char	*ft_f_precision(char *print_num, t_specs *utils)
{
	char	*final_num;

	utils->empty_spaces = 0;
	if (ft_strcmp(print_num, "+0") == 0 && utils->precision == 0)
		final_num = ft_strdup("+");
	else if ((int)ft_strlen(print_num) <= utils->precision)
	{
		final_num = ft_strnew(utils->precision);
		utils->empty_spaces = utils->precision - ft_strlen(print_num);
		if (ft_strchr(utils->flags, ' ') || (ft_strchr(utils->flags, '+')))
			utils->empty_spaces--;
		while (utils->empty_spaces > 0)
		{
			final_num = ft_strjoin_free_s2(" ", final_num);
			utils->empty_spaces--;
		}
		final_num = ft_strjoin_free_s2(print_num, final_num);
	}
	else
		final_num = ft_strdup(print_num);
	final_num = ft_cut_leftover(final_num, utils);
	free(print_num);
	return (final_num);
}

char	*f_width_emptyspcs(char *final_num, char *print_num, t_specs *utils)
{
	while (utils->empty_spaces > 0)
	{
		if (ft_iszero(utils) && !ft_strstr(print_num, "in") &&
		!(ft_strstr(print_num, "na")))
			final_num = ft_strjoin_free_s2("0", final_num);
		else
			final_num = ft_strjoin_free_s2(" ", final_num);
		utils->empty_spaces--;
	}
	return (final_num);
}

char	*ft_f_width(char *print_num, long double check_num, t_specs *utils)
{
	char	*final_num;

	if (((int)ft_strlen(print_num) < utils->width))
	{
		utils->empty_spaces = utils->width - (int)ft_strlen(print_num);
		final_num = ft_strnew(utils->width);
		if (ft_iszero(utils) && check_num >= 0 && (ft_strchr(utils->flags, ' ')
		|| (ft_strchr(utils->flags, '+'))))
			utils->empty_spaces--;
		final_num = f_width_emptyspcs(final_num, print_num, utils);
		if (ft_strchr(print_num, '-') && ft_strchr(final_num, '0'))
			print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
		if (ft_strchr(utils->flags, '+') && ft_strcmp(print_num, "inf") == 0)
			print_num = ft_strjoin_free_s2("+", print_num);
		final_num = ft_strjoin_free_s1(final_num, print_num);
		if (check_num < 0 && ft_strchr(final_num, '0') &&
		!ft_strchr(final_num, '-'))
			final_num = ft_strjoin_free_s2("-", final_num);
	}
	else
		final_num = ft_strdup(print_num);
	free(print_num);
	return (final_num);
}

char	*manage_f_width(char *print_num, long double check_num, int i,
t_specs *utils)
{
	if (ft_isdigit(utils->flags[i]) != 1)
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	if ((ft_strstr(print_num, "in") || (ft_strstr(print_num, "na")))
	&& utils->flags[0] == '.')
		print_num = ft_strdup(print_num);
	else
		print_num = ft_f_width(print_num, check_num, utils);
	return (print_num);
}

char	*manage_f_width_neg(char *print_num, int i, t_specs *utils)
{
	int	len_printnum;

	len_printnum = 0;
	if (ft_isdigit(utils->flags[i]) != 1)
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	if (ft_iszero(utils) && !ft_strchr(utils->flags, '+') &&
	!ft_strchr(utils->flags, ' '))
		print_num = ft_strsub(print_num, 1, (int)ft_strlen(print_num));
	while (*print_num == ' ')
		print_num++;	
	print_num = ft_strjoin("-", print_num);
	len_printnum = (int)ft_strlen(print_num);
	if (len_printnum < utils->width)
	{
		while (len_printnum < utils->width)
		{
			print_num = ft_strjoin_free_s2(" ", print_num);
			utils->width--;
		}
	}
	return (print_num);
}

char	*ft_f_manager(char *print_num, long double check_num, int is_neg,
t_specs *utils)
{
	int	i;

	i = 0;
	if (ft_strchr("0+-. ", utils->flags[i]))
		i++;
	if (ft_strchr(print_num, '-'))
		print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	if (ft_strcmp(print_num, "inf") != 0 && ft_strcmp(print_num, "-inf") != 0 &&
	ft_strcmp(print_num, "nan") != 0)
		print_num = ft_f_precision(print_num, utils);
	if (check_num < 0)
			print_num = ft_strjoin_free_s2("-", print_num);
	if (ft_strchr(utils->flags, '-') || ft_isdigit(utils->flags[i]) ||
	ft_iszero(utils))
		print_num = manage_f_width(print_num, check_num, i, utils);
	if (is_neg == 1 && !ft_strchr(print_num, '-'))
		print_num = manage_f_width_neg(print_num, i, utils);
	if (ft_strchr(utils->flags, '+') && is_neg == 0 &&
	!ft_strstr(print_num, "na") && !ft_strstr(print_num, "+"))
		print_num = ft_strjoin_free_s2("+", print_num);
	if (ft_strchr(utils->flags, ' ') && is_neg == 0 &&
	!ft_strchr(utils->flags, '+') && !ft_strstr(print_num, "na"))
		print_num = ft_strjoin_free_s2(" ", print_num);
	return (print_num);
}

char	*ft_check_inf_nan(char *print_num, long double check_num,
t_specs *utils)
{
	double	x;
	double	y;
	double	z;

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
		print_num = ft_itoa_float(check_num, utils->precision);
	return (print_num);
}

char	*ft_round_or_cut(char *print_num, long double check_num, t_specs *utils)
{
	long double		new_num;

	new_num = check_num * ft_x_to_power_n(utils->precision);
	if (new_num - (int)new_num > 0.5 || new_num - (int)new_num < -0.5)
		check_num = ft_round(check_num, utils->precision);
	else if (new_num - (int)new_num == 0.5 || new_num - (int)new_num == -0.5)
	{
		if (((int)new_num + 1) % 2 != 0)
			check_num = new_num / ft_x_to_power_n(utils->precision);
		else
			check_num = ft_round(check_num, utils->precision);
	}
	else
		check_num = ft_round(check_num, utils->precision);
	print_num = ft_check_inf_nan(print_num, check_num, utils);
	return (print_num);
}

int	conv_f(va_list *ap, t_specs *utils)
{
	char			*print_num;
	long double		check_num;
	int				len;
	int				is_neg;

	is_neg = 0;
	len = 0;
	print_num = NULL;
	check_num = ft_f_datatype(ap, utils);
/* 	if (ft_strchr(utils->flags, 'L'))
		check_num = va_arg(*ap, long double);
	else
		check_num = va_arg(*ap, double); */
	is_neg = ft_is_negative(check_num);
	if (ft_strchr(utils->flags, '.'))
		utils->precision = ft_atoi(ft_strchr(utils->flags, '.') + 1);
	else
		utils->precision = 6;
	print_num = ft_round_or_cut(print_num, check_num, utils);
	print_num = ft_f_manager(print_num, check_num, is_neg, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}

////////////////////////////////////////////PRINTF////////////////////////////////////////////////////////////////

void	init_specs(t_specs *utils)
{
	utils->flags = NULL;
	utils->precision = 0;
	utils->width = 0;
	utils->empty_spaces = 0;
	utils->c = '\0';
}

int	ft_print_reg_char(char format, int char_counter)
{
	ft_putchar(format);
	char_counter++;
	return (char_counter);
}

int ft_printf(const char *format, ...)
{
	va_list	ap;
	int		char_counter;
	int		i;
	int		in_conversion;
	t_specs *utils;

	char_counter = 0;
	i = -1;
	in_conversion = 0;
	va_start(ap, format);
	utils = (t_specs *)malloc(sizeof(t_specs));
	while (format[++i])
		if (format[i] == '%' && !in_conversion)
		{
			init_specs(utils);
			in_conversion = 1;
			char_counter += conversion_solver(&format[i], &ap, utils);
		}
		else if (!in_conversion)
			char_counter = ft_print_reg_char(format[i], char_counter);
		else if (is_conversion(format[i]))
			in_conversion = 0;
	free(utils);
	va_end(ap);
	return (char_counter);
}
