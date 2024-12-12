/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:48 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 23:57:26 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_exec(t_execution **stacks, t_execution *new)
{
	t_execution	*head;

	if (!*stacks)
	{
		*stacks = new;
		return ;
	}
	head = *stacks;
	while (head->next)
		head = head->next;
	head->next = new;
	new->next = NULL;
}

t_execution	*ft_lstnew_exec(int *fds, char **cmd, int cmdlen)
{
	t_execution	*list;

	list = (t_execution *)malloc(sizeof(t_execution));
	if (!list)
		return (NULL);
	list->cmd = cmd;
	list->fds = fds;
	list->cmd_len = cmdlen;
	list->next = NULL;
	return (list);
}

char	*add_to_cmd(char *data)
{
	data = ft_strdup(data);
	gc_add(0, data);
	return (data);
}

int	init_len_fds(int **fds, int *cmdlen, int *i, int *word_count)
{
	*cmdlen = *word_count;
	*fds = init_fds(*fds);
	*i = 0;
	return (*cmdlen);
}

t_execution	*process_command_tokens(t_token **curr, t_env *env)
{
	int		word_count;
	char	**cmd;
	int		*fds;
	int		i;
	int		cmdlen;

	word_count = count_words1(*curr);
	if (word_count == 0)
		return (NULL);
	fds = NULL;
	cmdlen = init_len_fds(&fds, &cmdlen, &i, &word_count);
	cmd = init_cmd_array(word_count);
	gc_add_double(0, (void **)cmd);
	while (*curr && (*curr)->value != PIPE)
	{
		if (if_redir(curr))
			handle_redirs(fds, curr, env);
		else if ((*curr)->value == WORD && i < word_count)
		{
			cmd[i] = add_to_cmd((*curr)->data);
			i++;
		}
		*curr = (*curr)->next;
	}
	return (ft_lstnew_exec(fds, cmd, cmdlen));
}
