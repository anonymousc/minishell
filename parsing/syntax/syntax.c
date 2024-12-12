/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:57 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 22:37:25 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*free_spaces(t_token *curr)
{
	while (curr && curr->value == WHITESPACE)
		curr = curr->next;
	return (curr);
}

int	check_pipe(t_token **final)
{
	t_token	*curr;

	curr = *final;
	if (curr && curr->value == PIPE)
		return (ft_printf(2, "syntax error\n"), 1);
	while (curr)
	{
		if (curr->value == PIPE)
		{
			if (!curr->next || curr->next->value == PIPE)
				return (ft_printf(2, "syntax error\n"), 1);
			curr = curr->next;
			if (curr->value == WHITESPACE)
			{
				curr = free_spaces(curr);
				if (!curr || curr->value == PIPE)
					return (ft_printf(2, "syntax error\n"), 1);
			}
		}
		if (curr)
			curr = curr->next;
	}
	return (0);
}

int	check_heredoc(t_token **final)
{
	t_token	*curr;

	curr = *final;
	while (curr)
	{
		if (curr->value == HEREDOC || curr->value == APPEND)
		{
			if (!curr->next || curr->next->value == HEREDOC
				|| curr->next->value == PIPE || curr->next->value == APPEND
				|| curr->next->value == REDIRECTION_IN
				|| curr->next->value == REDIRECTION_OUT)
				return (ft_printf(2, "syntax error\n"), 1);
			curr = curr->next;
			if (curr->value == WHITESPACE)
			{
				curr = free_spaces(curr);
				if (!curr || curr->value == PIPE || if_redir_data(curr))
					return (ft_printf(2, "syntax error\n"), 1);
			}
		}
		if (curr)
			curr = curr->next;
	}
	return (0);
}

int	check_redir(t_token **final)
{
	t_token	*curr;

	curr = *final;
	while (curr)
	{
		if (curr->value == REDIRECTION_IN || curr->value == REDIRECTION_OUT)
		{
			if (!curr->next || curr->next->value == HEREDOC
				|| curr->next->value == PIPE || curr->next->value == APPEND
				|| curr->next->value == REDIRECTION_OUT
				|| curr->next->value == REDIRECTION_IN)
				return (ft_printf(2, "syntax error\n"), 1);
			curr = curr->next;
			if (curr->value == WHITESPACE)
			{
				curr = free_spaces(curr);
				if (!curr || curr->value == PIPE || if_redir_data(curr))
					return (ft_printf(2, "syntax error\n"), 1);
			}
		}
		if (curr)
			curr = curr->next;
	}
	return (0);
}
