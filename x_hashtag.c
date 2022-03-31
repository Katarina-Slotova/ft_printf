/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_hashtag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:20:55 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:23:57 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (ft_strchr(utils->flags, '-')
		|| ft_strchr(utils->flags, ft_isdigit(*utils->flags)))
			final_num = ft_hashtag_width_x(print_num, final_num, utils);
	else
	{
		if (utils->c == 'x')
			final_num = ft_strjoin_free_s2("0x", print_num);
		else if (utils->c == 'X')
			final_num = ft_strjoin_free_s2("0X", print_num);
	}
	return (final_num);
}
