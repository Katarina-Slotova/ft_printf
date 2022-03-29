/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:13:03 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/29 16:11:27 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

typedef struct t_list
{
	char	*flags;
	int		width;
	int		precision;
	int		empty_spaces;
	char	c;
}				t_specs;

int		ft_printf(const char *format, ...);
int		conv_c(va_list *ap, t_specs *utils);
int		conv_s(va_list *ap, t_specs *utils);
int		conv_p(va_list *ap, t_specs *utils);
int		conv_d_i(va_list *ap, t_specs *utils);
int		conv_o(va_list *ap, t_specs *utils);
int		conv_u(va_list *ap, t_specs *utils);
int		conv_x(va_list *ap, t_specs *utils);
int		conv_f(va_list *ap, t_specs *utils);
int		conv_percent(t_specs *utils);
int		conversion_solver(const char *format, va_list *ap, t_specs *utils);
int		is_conversion(char c);
int		is_flag(char c);

#endif
