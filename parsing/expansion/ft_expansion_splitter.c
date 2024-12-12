/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_splitter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:20 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 22:41:32 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(char *str)
{
	int		is_word;
	size_t	counter;

	counter = 0;
	is_word = 0;
	while (*str)
	{
		if (*str == is_space_delta(*str))
			is_word = 0;
		else
		{
			if (is_word == 0)
			{
				is_word = 1;
				counter++;
			}
		}
		str++;
	}
	return (counter);
}

static char	*allocate(char **s)
{
	char	*word;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != is_space_delta((*s)[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while ((*s)[i] && (*s)[i] != is_space_delta((*s)[i]))
	{
		word[i] = (*s)[i];
		i++;
	}
	word[i] = '\0';
	*s += i + 1;
	return (word);
}

char	**ft_split_expander(char *s)
{
	char	**splitted;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s);
	splitted = (char **)malloc(sizeof(char *) * (words + 1));
	if (!splitted)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == is_space_delta(*s))
			s++;
		if (*s && *s != is_space_delta(*s))
			splitted[i] = allocate(&s);
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}
