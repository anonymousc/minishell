/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:07 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:35:02 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separators(char c)
{
	if (c == '|' || c == '>' || c == '<' || is_space(c))
		return (1);
	return (0);
}

t_Token	get_token(char *str)
{
	if (ft_strnstr(str, "|", 1))
		return (PIPE);
	else if (ft_strnstr(str, "<<", 2))
		return (HEREDOC);
	else if (ft_strnstr(str, ">>", 2))
		return (APPEND);
	else if (ft_strnstr(str, ">", 1))
		return (REDIRECTION_OUT);
	else if (ft_strnstr(str, "<", 1))
		return (REDIRECTION_IN);
	else if (ft_strnstr(str, " ", 1) || ft_strnstr(str, "\n", 1)
		|| ft_strnstr(str, "\v", 1) || ft_strnstr(str, "\t", 1)
		|| ft_strnstr(str, "\r", 1))
		return (WHITESPACE);
	return (WORD);
}

char	*ft_strdup_and_inc(char *src, char **s)
{
	size_t	i;
	char	*duplicate;

	if (!src)
		return (NULL);
	duplicate = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src[i])
	{
		duplicate[i] = src[i];
		i++;
	}
	duplicate[i] = '\0';
	*s += ft_strlen(src);
	return (duplicate);
}

char	*split_each_token(char *s, char **str, int *i)
{
	t_Token	t;

	t = get_token(s);
	if (t == PIPE)
		str[(*i)] = ft_strdup_and_inc("|", &s);
	else if (t == HEREDOC)
		str[(*i)] = ft_strdup_and_inc("<<", &s);
	else if (t == APPEND)
		str[(*i)] = ft_strdup_and_inc(">>", &s);
	else if (t == REDIRECTION_IN)
		str[(*i)] = ft_strdup_and_inc("<", &s);
	else if (t == REDIRECTION_OUT)
		str[(*i)] = ft_strdup_and_inc(">", &s);
	else if (t == WHITESPACE)
		str[(*i)] = ft_strdup_and_inc(is_space_veta(*s), &s);
	return (s);
}
