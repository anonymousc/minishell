/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:17 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 22:25:18 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

int	check_is_same_quotes2(char c1, char c2)
{
	return (c1 == c2);
}

char	*quotes_holder(char *s)
{
	char	quote;

	quote = (*s)++;
	while (s && *s && !check_is_same_quotes2(*s, quote))
		s++;
	return (s);
}

char	*quotes_holder2(char *s, int *i)
{
	char	quote;

	(*i) = 0;
	quote = (*i)++;
	while (s && s[(*i)] && !check_is_same_quotes2(s[(*i)], quote))
		(*i)++;
	return (s);
}
