/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:13:03 by kslotova          #+#    #+#             */
/*   Updated: 2022/03/31 17:27:55 by kslotova         ###   ########.fr       */
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
	int		in_conversion;
}				t_specs;

int						ft_printf(const char *format, ...);
int						conversion_solver(const char *format, va_list *ap,
						t_specs *utils);
int						conv_c(va_list *ap, t_specs *utils);
int						conv_s(va_list *ap, t_specs *utils);
int						conv_p(va_list *ap, t_specs *utils);
int						conv_d_i(va_list *ap, t_specs *utils);
int						conv_o(va_list *ap, t_specs *utils);
int						conv_u(va_list *ap, t_specs *utils);
int						conv_x(va_list *ap, t_specs *utils);
int						conv_f(va_list *ap, t_specs *utils);
int						conv_percent(t_specs *utils);
int						ft_iszero(t_specs *utils);
int						is_conversion(char c);
int						is_flag(char c);
char					*dio_width_emptyspaces(t_specs *utils, char *final_num);
char					*ft_itoa_hex(uintmax_t num, int base, t_specs *utils);
char					*ft_o_precision(char *print_num, t_specs *utils);
char					*ft_o_width(char *print_num, t_specs *utils);
char					*f_width_emptyspaces(char *final_num, char *print_num,
						t_specs *utils);
char					*ft_check_inf_nan(char *print_num, 
						long double check_num, t_specs *utils);
unsigned long long int	ft_oux_datatype(va_list *ap, t_specs *utils);
long long int			ft_di_datatype(va_list *ap, t_specs *utils);
long double				ft_f_datatype(va_list *ap, t_specs *utils);
char					*manage_f_width_neg(char *print_num, int i,
						t_specs *utils);
char					*manage_f_width(char *print_num, long double check_num,
						int i, t_specs *utils);
char					*di_width_flags(char *final_num,
						long long int check_num, t_specs *utils);
char					*di_width_above_prec(char *print_num,
						long long int check_num, t_specs *utils);
char					*ft_di_width(char *print_num, long long int check_num,
						t_specs *utils);
char					*ft_di_precision(char *print_num,
						long long int check_num, t_specs *utils);
char					*ft_itoa_hex(uintmax_t num, int base, t_specs *utils);
char					*ft_hashtag_x(char *print_num, t_specs *utils);
char					*di_prec_not_zero(char *print_num,
						long long int check_num, t_specs *utils);

#endif
