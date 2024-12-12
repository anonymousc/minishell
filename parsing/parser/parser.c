/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:51 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 02:47:44 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd_(int *fd, int *fd2)
{
	*fd = -1;
	*fd2 = -1;
}

void	handle_redirs(int *fds, t_token **curr, t_env *env)
{
	if ((*curr)->value == REDIRECTION_IN)
		fds[1] = handle_input_redirection_parser(curr, &fds[0], &fds[2], env);
	else if ((*curr)->value == REDIRECTION_OUT && !fds[5])
	{
		if (ft_strchr((*curr)->next->data, '$'))
		{
			(*curr)->next->data = ft_strjoin2(
					before_dollar_word((*curr)->next->data),
					expander(ft_strchr((*curr)->next->data, '$'), env));
			gc_add(0, (*curr)->next->data);
			if (ft_strchr_for_space((*curr)->next->data)
				|| !(*curr)->next->data)
				fds[0] = -3;
		}
		if (fds[0] != -3)
			fds[0] = handle_output_redirection_parser(curr, &fds[4], &fds[5]);
	}
	else if ((*curr)->value == HEREDOC)
		handle_heredoc_parser(&fds[3], curr, env);
	else if ((*curr)->value == APPEND)
		handle_append_parser(&fds, &fds[4], curr, env);
}

void	for_execute(t_token **final, t_execution **data, t_env *env)
{
	t_token		*curr;
	t_execution	*new_cmd;

	*data = NULL;
	curr = *final;
	while (curr)
	{
		new_cmd = process_command_tokens(&curr, env);
		gc_add(0, new_cmd);
		if (new_cmd)
		{
			if (!*data)
				*data = new_cmd;
			else
				ft_lstadd_back_exec(data, new_cmd);
		}
		if (curr && curr->value == PIPE)
			curr = curr->next;
	}
}
