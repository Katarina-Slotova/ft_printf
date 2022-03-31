/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:56:56 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 16:40:43 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

	ptr = va_arg(*ap, void *);
	final_ptr = ft_itoa_hex((uintptr_t)ptr, 16, utils);
	final_ptr = ft_strjoin_free_s2("0x", final_ptr);
		final_ptr = ft_ptr_manager(final_ptr, utils);
	ft_putstr(final_ptr);
	len = ft_strlen(final_ptr);
	free(final_ptr);
	return (len);
}
