/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:04:49 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:27:09 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_di_negative_num(char *final_num, char *print_num,
long long int check_num, t_specs *utils)
{
	char	*final_num2;

	final_num = dio_width_emptyspaces(utils, final_num);
	final_num2 = di_width_flags(final_num, check_num, utils);
	if (check_num < 0 && ft_strchr(utils->flags, '.'))
		final_num2 = ft_strjoin_free_s1(final_num2, "-");
	else if (ft_iszero(utils))
		final_num2 = ft_strjoin_free_s2("-", final_num2);
	else
		final_num2 = ft_strjoin_free_s1(final_num2, "-");
	print_num = ft_strsub(print_num, 1, ft_strlen(print_num));
	final_num2 = ft_strjoin_free_s2(final_num2, print_num);
	return (final_num2);
}

char	*di_width_flags(char *final_num, long long int check_num,
t_specs *utils)
{
	char	*final_num2;

	final_num2 = NULL;
	if (ft_strchr(utils->flags, '+') && !ft_iszero(utils) && check_num >= 0
		&& !ft_strchr(utils->flags, '.'))
	{
		final_num = ft_strsub(final_num, 1, utils->width);
		final_num2 = ft_strjoin_free_s1(final_num, "+");
	}
	else if ((ft_strchr(utils->flags, '+') || ft_strchr(utils->flags, ' '))
		&& !ft_strchr(utils->flags, '.') && ft_iszero(utils) && check_num >= 0)
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
	if (ft_strchr(utils->flags, ' ') && !ft_strchr(utils->flags, '.')
		&& check_num >= 0)
	{
		final_num = ft_strjoin_free_s2(" ", final_num);
		utils->empty_spaces--;
	}
	while (utils->empty_spaces-- > 0)
		final_num = ft_strjoin_free_s1(final_num, " ");
	return (final_num);
}

char	*di_width_above_numlen(char *final_num, char *print_num,
long long int check_num, t_specs *utils)
{
	if (ft_strchr(utils->flags, '-'))
		final_num = di_width_minusflag(final_num, print_num, check_num, utils);
	else if ((ft_iszero(utils) || ft_strchr(utils->flags, '+'))
		&& check_num < 0)
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
	if (ft_strchr(utils->flags, ' ') && !ft_strchr(utils->flags, '.')
		&& check_num >= 0 && checker == 0)
		final_num = ft_strjoin_free_s2(" ", final_num);
	free(print_num);
	return (final_num);
}
