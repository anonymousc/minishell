/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:17 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 05:32:24 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar_expansion(t_token *curr, t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (curr->data[i])
	{
		if (curr->data[i] == '$')
		{
			tmp = expander(curr->data + i, env);
			*(curr->data + i) = '\0';
			if (tmp && *tmp)
			{
				curr->data = ft_strjoin(curr->data, tmp);
				gc_add(0, curr->data);
			}
			else
				*(curr->data + i) = '\0';
		}
		i++;
	}
}

static void	handle_space_expansion(t_token **final, \
t_token **curr, t_token *prev, char *tmp)
{
	char	**split;
	char	**next;
	t_token	*last;

	split = ft_split_expander(tmp);
	gc_add_double(0, (void **)split);
	next = token_to_char((*curr)->next);
	if (*final == *curr)
	{
		*final = make_token_list(split);
		*curr = *final;
		while (*curr && (*curr)->next)
			*curr = (*curr)->next;
		(*curr)->next = make_token_list2(next);
	}
	else
	{
		*curr = make_token_list(split);
		last = ft_lstlast(*curr);
		prev->next = *curr;
		last->next = make_token_list2(next);
	}
}

static void	expand_token(t_token **final, t_token **curr, t_token *prev,
		t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*curr)->data[i])
	{
		if ((*curr)->data[i] == '$')
		{
			tmp = expander((*curr)->data + i, env);
			*((*curr)->data + i) = '\0';
			if (tmp && *tmp)
			{
				tmp = ft_strjoin((*curr)->data, tmp);
				gc_add(0, tmp);
				if (ft_strchr_for_space(tmp))
					handle_space_expansion(final, curr, prev, tmp);
				else
					(*curr)->data = tmp;
			}
			else
				*((*curr)->data + i) = '\0';
		}
		i++;
	}
}

void	expander_final(t_token **final, t_env *env)
{
	t_token	*curr;
	t_token	*prev;

	curr = *final;
	prev = NULL;
	while (curr)
	{
		if (if_redir_data(curr) && curr->next)
		{
			if (curr->next->next)
				curr = curr->next->next;
			else
				curr = curr->next;
		}
		else if (curr->value == WORD)
		{
			if (check_in_db_or_sq(curr->data) == 2)
				handle_dollar_expansion(curr, env);
			else if (!check_in_db_or_sq(curr->data))
				expand_token(final, &curr, prev, env);
		}
		prev = curr;
		curr = curr->next;
	}
	extra_sanitize(final);
}
