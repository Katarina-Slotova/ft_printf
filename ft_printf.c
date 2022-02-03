/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:12:28 by katarinka         #+#    #+#             */
/*   Updated: 2022/02/03 18:04:28 by katarinka        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcharjoin(char *old_str, char c)
{
	char	*new_str;
	int		i;

	new_str = ft_strnew(ft_strlen(old_str) + 2);
	i = ft_strlen(new_str);
	ft_bzero(new_str, i);
	new_str = ft_strcpy(new_str, old_str);
	new_str[i] = c;
	return (new_str);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int		char_counter;
	int		i;
	char	*final_str;

	char_counter = 0;
	i = 0;
	final_str = (char *)malloc(sizeof(char));
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			//conversion handler -- maybe a separate function for that
			char_counter += conversion_solver(&format, &ap);
		else
		{
			//just add the printable character as received to the previously saved string of chars to be printed - 
			//write a strcharjoin function for this;
			final_str = ft_strcharjoin(final_str, format[i]);
			char_counter++;
		}
		i++;
	}
	write(1, final_str, ft_strlen(final_str));
	free(final_str);
	va_end(ap);
	return (char_counter);
}
