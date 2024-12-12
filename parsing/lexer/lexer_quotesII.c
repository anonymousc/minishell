/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotesII.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:32 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 23:54:19 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	word_delim(char const *s)
{
	size_t		counter;
	int			in_word;
	char const	*p;
	int			i;

	i = 0;
	counter = 0;
	p = s;
	while (p && *p)
	{
		in_word = 0;
		if (is_quotes(*p))
		{
			p = quotes_holder2((char *)p, &i);
			counter++;
		}
		else if (is_separators(*p) || in_word == 0)
		{
			in_word = 1;
			counter++;
		}
		p++;
	}
	return (counter);
}

int	quotes_cout_word(char *s, char q)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != q)
		i++;
	return (i);
}
