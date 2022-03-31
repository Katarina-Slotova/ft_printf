/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_width.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:16 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:22:00 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_f_width(char *print_num, long double check_num, t_specs *utils)
{
	char	*ret_n;

	if (((int)ft_strlen(print_num) < utils->width))
	{
		utils->empty_spaces = utils->width - (int)ft_strlen(print_num);
		ret_n = ft_strnew(utils->width);
		if (ft_iszero(utils) && check_num >= 0 && (ft_strchr(utils->flags, ' ')
				|| (ft_strchr(utils->flags, '+'))))
			utils->empty_spaces--;
		ret_n = f_width_emptyspaces(ret_n, print_num, utils);
		if (ft_strchr(print_num, '-') && ft_strchr(ret_n, '0'))
			print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
		if (ft_strchr(utils->flags, '+') && ft_strcmp(print_num, "inf") == 0)
			print_num = ft_strjoin_free_s2("+", print_num);
		if (ft_strchr(utils->flags, '-'))
			ret_n = ft_strjoin_free_s2(print_num, ret_n);
		else
			ret_n = ft_strjoin_free_s1(ret_n, print_num);
		if (check_num < 0 && ft_strchr(ret_n, '0') && !ft_strchr(ret_n, '-'))
			ret_n = ft_strjoin_free_s2("-", ret_n);
	}
	else
		ret_n = ft_strdup(print_num);
	free(print_num);
	return (ret_n);
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
	if (ft_iszero(utils) && !ft_strchr(utils->flags, '+')
		&& !ft_strchr(utils->flags, ' '))
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
