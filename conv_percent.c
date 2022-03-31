/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:57:03 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:41:18 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_percent_width(t_specs *utils)
{
	int	total_width;

	total_width = utils->width;
	if (ft_strchr(utils->flags, '-'))
	{
		write(1, "%", 1);
		utils->width--;
		while (utils->width-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (utils->width-- > 1)
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
