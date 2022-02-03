/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:41:04 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/01 18:47:06 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (i);
}

static int	find_end(const char *s)
{
	int	str_len;

	str_len = ft_strlen(s);
	if (!s)
		return (0);
	while (str_len != 0 && (s[str_len] == '\0' || s[str_len] == ' '
			|| s[str_len] == '\t' || s[str_len] == '\n'))
		str_len--;
	return (str_len);
}

static char	*ft_trim(char *trimmed_str, const char *s, int end_i, int start_i)
{
	int	i;

	i = 0;
	while (end_i > start_i)
	{
		trimmed_str[i] = s[start_i];
		start_i++;
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

char	*ft_strtrim(char const *s)
{
	int		start_i;
	int		end_i;
	int		trim_len;
	char	*trimmed_str;

	if (!s)
		return (0);
	start_i = find_start(s);
	end_i = find_end(s);
	if (start_i <= end_i++)
		trim_len = end_i - start_i;
	else
		trim_len = 0;
	trimmed_str = (char *)malloc(sizeof(char) * (trim_len + 1));
	if (!trimmed_str)
		return (NULL);
	trimmed_str = ft_trim(trimmed_str, s, end_i, start_i);
	return (trimmed_str);
}
