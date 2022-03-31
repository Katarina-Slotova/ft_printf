/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_datatype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:57:31 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:18:28 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long int	ft_oux_datatype(va_list *ap, t_specs *utils)
{
	if (ft_strstr(utils->flags, "hh"))
		return ((unsigned char)va_arg(*ap, unsigned int));
	else if (ft_strchr(utils->flags, 'h'))
		return ((unsigned short int)va_arg(*ap, unsigned int));
	else if (ft_strchr(utils->flags, 'l'))
		return (va_arg(*ap, unsigned long int));
	else if (ft_strstr(utils->flags, "ll"))
		return (va_arg(*ap, unsigned long long int));
	else
		return (va_arg(*ap, unsigned int));
}

long long int	ft_di_datatype(va_list *ap, t_specs *utils)
{
	if (ft_strstr(utils->flags, "hh"))
		return ((signed char)va_arg(*ap, int));
	else if (ft_strchr(utils->flags, 'h'))
		return ((short int)va_arg(*ap, int));
	else if (ft_strchr(utils->flags, 'l'))
		return (va_arg(*ap, long int));
	else if (ft_strstr(utils->flags, "ll"))
		return (va_arg(*ap, long long int));
	else
		return (va_arg(*ap, int));
}

long double	ft_f_datatype(va_list *ap, t_specs *utils)
{
	if (ft_strchr(utils->flags, 'L'))
		return (va_arg(*ap, long double));
	else
		return (va_arg(*ap, double));
}
