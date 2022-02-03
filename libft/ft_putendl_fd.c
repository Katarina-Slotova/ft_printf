/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:39:29 by kslotova          #+#    #+#             */
/*   Updated: 2021/11/29 11:45:17 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	int	a;

	a = 0;
	if (s)
	{
		while (s[a] != '\0')
		{
			ft_putchar_fd(s[a], fd);
			a++;
		}
		ft_putchar_fd('\n', fd);
	}
}
