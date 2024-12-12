/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:31 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 05:38:19 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token_list2(char **split)
{
	t_token	*head;
	t_token	*new_token;
	t_token	*curr;
	int		i;

	head = NULL;
	new_token = NULL;
	curr = NULL;
	i = 0;
	while (split && split[i])
	{
		new_token = malloc(sizeof(t_token));
		gc_add(0, new_token);
		new_token->data = ft_strdup(split[i]);
		gc_add(0, new_token->data);
		new_token->value = get_token(split[i]);
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			curr->next = new_token;
		curr = new_token;
		i++;
	}
	return (head);
}

char	**token_to_char(t_token *list)
{
	char	**split;
	int		i;

	split = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	i = 0;
	while (list)
	{
		split[i] = list->data;
		i++;
		list = list->next;
	}
	split[i] = NULL;
	gc_add(0, split);
	return (split);
}

t_token	*update_prev(t_token *prev, t_token *current, t_token *tmp)
{
	while (prev && prev->next != tmp)
		prev = prev->next;
	if (prev)
		prev->next = current;
	return (prev);
}

void	extra_sanitize(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*prev;

	current = *head;
	while (current && current->next)
	{
		if (current->value == WORD && !(*current->data)
			&& current->next->value == WORD)
		{
			tmp = current;
			current = current->next;
			if (tmp == *head)
				*head = current;
			else
			{
				prev = *head;
				prev = update_prev(prev, current, tmp);
			}
			gc_add(0, tmp);
		}
		else
			current = current->next;
	}
}

int	if_redir_data(t_token *curr)
{
	return (curr->value == HEREDOC || curr->value == REDIRECTION_IN
		|| curr->value == REDIRECTION_OUT || curr->value == APPEND);
}
