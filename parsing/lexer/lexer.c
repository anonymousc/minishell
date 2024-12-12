/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:39 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 23:53:20 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*qoutes_detailer(char *s, char **str, int *i)
{
	char	q;

	q = *s;
	str[(*i)] = ft_substr(s, 0, quotes_cout_word(s + 1, q) + 2);
	s += quotes_cout_word(s + 1, q) + 2;
	(*i)++;
	return (s);
}

static char	*skip_checker(char *s, int *len)
{
	char	*start;

	start = s;
	while ((*s && !(is_separators(*s) || is_quotes(*s))))
		(s)++;
	*len = s - start;
	return (s);
}

static char	*isnt_asep(char **str, int *i, int *len, char *start)
{
	str[(*i)] = (char *)malloc(((*len) + 1) * sizeof(char));
	ft_memcpy(str[(*i)], start, (*len));
	str[(*i)][(*len)] = '\0';
	return (str[(*i)]);
}

static char	**str_all_fill_v2(char **str, char const *s)
{
	const char	*start;
	int			i;
	int			len;

	i = 0;
	while (s && *s)
	{
		if (is_quotes(*s))
			s = qoutes_detailer((char *)s, str, &i);
		else if (is_separators(*s))
		{
			s = split_each_token((char *)s, str, &i);
			i++;
		}
		else if (!is_separators(*s))
		{
			start = s;
			s = skip_checker((char *)s, &len);
			str[i++] = isnt_asep(str, &i, &len, (char *)start);
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**split_to_lex(char *s)
{
	char	**str;
	char	**to_free;

	if (!s)
		return (NULL);
	str = malloc((word_delim(s) + 1) * sizeof(char *));
	to_free = str_all_fill_v2(str, s);
	gc_add_double(0, (void **)to_free);
	return (to_free);
}
