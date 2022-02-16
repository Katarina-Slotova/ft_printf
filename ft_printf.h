/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:13:03 by katarinka         #+#    #+#             */
/*   Updated: 2022/02/16 12:12:24 by katarinka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

int 	ft_printf(const char *format, ...);
int		conv_c(va_list *ap, char *flags_collector);
int		conv_s(va_list *ap, char *flags_collector);
int		conv_p(va_list *ap, char *flags_collector, char conversion);
int		conv_d_i(va_list *ap, char *flags_collector);
int		conv_o(va_list *ap, char *flags_collector);
int		conv_u(va_list *ap, char *flags_collector);
int		conv_x(va_list *ap, char *flags_collector, char conversion);
int		conv_f(va_list *ap, char *flags_collector);
int		conv_percent();
int		conversion_solver(const char *format, va_list *ap);
int		is_conversion(char c);
int		is_flag(char c);
char	*ft_strcharjoin(char *old_str, char c);


#endif
