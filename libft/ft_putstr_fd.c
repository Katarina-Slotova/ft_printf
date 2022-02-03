/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:23:19 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/25 10:56:24 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	a;

	a = 0;
	if (!s)
		return ;
	while (s[a] != '\0')
	{
		ft_putchar_fd(s[a], fd);
		a++;
	}
}
