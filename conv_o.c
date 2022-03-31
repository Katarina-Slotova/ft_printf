/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:56:47 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:39:42 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	while (utils->flags[i] && ft_isdigit(utils->flags[i]) != 1
		&& !ft_strchr(utils->flags, 'h'))
		i++;
	utils->width = ft_atoi(&utils->flags[i]);
	if (utils->width < 0)
		utils->width *= -1;
	if (ft_strchr(utils->flags, '#') && !ft_strchr(utils->flags, '.')
		&& check_num != 0)
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
		if ((print_num[0] == '\0' || print_num[0] == '0')
			&& ft_strchr(utils->flags, '#') && utils->precision == 0)
			print_num = ft_strdup("0");
		else
		{
			if (ft_strchr(utils->flags, '#'))
				print_num = ft_strjoin_free_s2("0", print_num);
			print_num = ft_o_precision(print_num, utils);
		}
	}
	if (ft_strchr(utils->flags, '-') || ft_isdigit(*utils->flags)
		|| ft_strchr(utils->flags, '#'))
		print_num = ft_manage_o_width(print_num, check_num, i, utils);
	return (print_num);
}

int	conv_o(va_list *ap, t_specs *utils)
{
	char					*print_num;
	unsigned long long int	check_num;
	int						len;

	len = 0;
	check_num = ft_oux_datatype(ap, utils);
	print_num = ft_itoa_base_u(check_num, 8);
	print_num = ft_o_manager(print_num, check_num, utils);
	ft_putstr(print_num);
	len = ft_strlen(print_num);
	free(print_num);
	return (len);
}
