/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:45 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 22:34:26 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_db_or_sq(char *s)
{
	int	dq;
	int	sq;
	int	i;

	dq = 0;
	sq = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && !sq)
			dq = 1;
		if (s[i] == '\'' && !dq)
			sq = 1;
		i++;
	}
	if (dq)
		return (2);
	if (sq)
		return (1);
	return (0);
}

char	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	if (c == '"')
		return ('"');
	return (0);
}

int	count_chars_after_removal(char *s)
{
	int		count;
	int		in_dquote;
	int		in_squote;
	char	q;

	count = 0;
	in_dquote = 0;
	in_squote = 0;
	while (s && *s)
	{
		q = is_quote(*s);
		if (q == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (q == '\'' && !in_dquote)
			in_squote = !in_squote;
		else
			count++;
		s++;
	}
	return (count);
}

char	*remove_quotes(char *s)
{
	t_quotes	data;
	char		*result;

	data.len = count_chars_after_removal(s);
	result = malloc(sizeof(char) * (data.len + 1));
	data.j = 0;
	data.i = 0;
	data.in_dquote = 0;
	data.in_squote = 0;
	while (s && s[data.i])
	{
		data.q = is_quote(s[data.i]);
		if (data.q == '"' && !data.in_squote)
			data.in_dquote = !data.in_dquote;
		else if (data.q == '\'' && !data.in_dquote)
			data.in_squote = !data.in_squote;
		else
			result[data.j++] = s[data.i];
		data.i++;
	}
	result[data.j] = '\0';
	return (result);
}

void	process_quotes(t_token **final)
{
	t_token	*curr;
	char	*processed;

	curr = *final;
	while (curr)
	{
		if (curr->value == HEREDOC && curr->next->next)
			curr = curr->next->next;
		else if (curr->value == WORD)
		{
			processed = remove_quotes(curr->data);
			gc_add(0, processed);
			curr->data = processed;
		}
		curr = curr->next;
	}
}
