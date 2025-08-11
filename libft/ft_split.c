/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unadoroz <unadoroz@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:08:43 by unadoroz          #+#    #+#             */
/*   Updated: 2025/05/05 09:46:29 by unadoroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	words;
	int	in_word;

	words = 0;
	in_word = 0;
	if (!s)
		return (0);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			words++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (words);
}

static char	**free_mem(char **sub_str, int word_index)
{
	while (word_index > 0)
	{
		if (sub_str[word_index - 1])
		{
			free(sub_str[word_index - 1]);
			sub_str[word_index - 1] = NULL;
		}
		word_index--;
	}
	if (sub_str)
	{
		free(sub_str);
		sub_str = NULL;
	}
	return (NULL);
}

static int	add_word(char **sub_str, const char *s, char c, int word_index)
{
	int	word_len;

	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	sub_str[word_index] = ft_substr(s, 0, word_len);
	if (!sub_str[word_index])
		return (0);
	return (word_len);
}

char	**ft_split(char const *s, char c)
{
	int		word_len;
	int		word_index;
	char	**sub_str;

	if (!s)
		return (NULL);
	sub_str = (char **)malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (!sub_str)
		return (NULL);
	word_index = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			word_len = add_word(sub_str, s, c, word_index);
			if (word_len == 0)
				return (free_mem(sub_str, word_index));
			word_index++;
			s += word_len;
		}
	}
	sub_str[word_index] = NULL;
	return (sub_str);
}
