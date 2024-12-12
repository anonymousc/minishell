/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:43 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 23:40:46 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_token **data)
{
	int		wc;
	t_token	*curr;

	wc = 0;
	curr = *data;
	while (curr)
	{
		if (curr && (curr->value == REDIRECTION_IN
				|| curr->value == REDIRECTION_OUT))
			curr = curr->next->next;
		if (curr && curr->value == WORD)
			wc++;
		if (curr)
			curr = curr->next;
	}
	return (wc);
}

int	cmd_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	count_words1(t_token *tokens)
{
	int		word_count;
	t_token	*temp;

	word_count = 0;
	temp = tokens;
	while (temp && temp->value != PIPE)
	{
		if (temp->value == WORD)
			word_count++;
		temp = temp->next;
	}
	return (word_count);
}

char	**init_cmd_array(int word_count)
{
	char	**cmd;
	int		k;

	cmd = (char **)malloc(sizeof(char *) * (word_count + 1));
	k = -1;
	while (++k <= word_count)
		cmd[k] = NULL;
	return (cmd);
}

int	*init_fds(int *array)
{
	int	i;

	i = 0;
	array = malloc(sizeof(int) * 7);
	gc_add(0, array);
	if (!array)
		return (NULL);
	while (i < 7)
	{
		if (i == 0 || i == 2)
			array[i] = 1;
		else
			array[i] = 0;
		i++;
	}
	return (array);
}
