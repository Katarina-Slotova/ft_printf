/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:56:26 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:35:18 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_minus(char c, t_specs *utils)
{
	ft_putchar(c);
	utils->width--;
	while (utils->width > 0)
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
		while (utils->width > 1)
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
