/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:57:07 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:42:05 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

	check_str = va_arg(*ap, char *);
	if (check_str == NULL)
		print_str = ft_strdup("(null)");
	else
		print_str = ft_strdup(check_str);
	print_str = ft_str_manager(print_str, utils);
	ft_putstr(print_str);
	len = ft_strlen(print_str);
	free(print_str);
	return (len);
}
