/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslotova <kslotova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:07:08 by kslotova          #+#    #+#             */
/*   Updated: 2021/12/02 17:55:25 by kslotova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			words++;
		while (str[i] != c && str[i])
			i++;
	}
	return (words);
}

static int	word_length(const char *str, char c)
{
	int	i;
	int	word_len;

	i = 0;
	word_len = 0;
	if (!str)
		return (0);
	while (str[i] == c && str[i])
		i++;
	while (str[i] != c && str[i])
	{
		word_len++;
		i++;
	}
	return (word_len);
}

static void	*ft_free(char **res, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(res[i++]);
	free(res);
	return (0);
}

static char	**ft_split(const char *str, char c, size_t words, char **new_str)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	while (i < words)
	{
		x = 0;
		new_str[i] = (char *)malloc(sizeof(char)
				* (word_length(&str[j], c) + 1));
		if (!new_str[i])
			return (ft_free(new_str, i));
		while (str[j] == c)
			j++;
		while (str[j] != c && str[j])
			new_str[i][x++] = str[j++];
		new_str[i][x] = '\0';
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t	words;
	char	**new_str;

	if (!s)
		return (0);
	words = word_count(s, c);
	new_str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!new_str)
		return (0);
	return (ft_split(s, c, words, new_str));
}
