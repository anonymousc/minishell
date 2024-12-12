/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:51 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/13 00:07:14 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ambugious_redirection(char *data, t_env *env)
{
	data = ft_strjoin2(before_dollar_word(data), expander(ft_strchr(data, '$'),
				env));
	gc_add(0, data);
	return (data);
}

void	check_validity(char *data, int *fd_out, int *fflag)
{
	if (*fd_out != -3)
		*fd_out = open(data, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (access(data, R_OK | W_OK) == -1)
		*fflag = 1;
	if (!ft_strncmp(data, "/dev/stdout", ft_strlen("/dev/stdout")) && !data)
		(*fd_out)--;
}

void	init_fd_(int *fd, int *fd2)
{
	*fd = -1;
	*fd2 = -1;
}

void	handle_redirs(int *fds, t_token **curr, t_env *env)
{
	if ((*curr)->value == REDIRECTION_IN)
		fds[1] = handle_input_redirection_parser(curr, fds, &fds[4], env);
	else if ((*curr)->value == REDIRECTION_OUT && !fds[5])
		fds[0] = handle_output_redirection_parser(curr, &fds[4], &fds[5], env);
	else if ((*curr)->value == HEREDOC)
		handle_heredoc_parser(&fds[3], curr, env);
	else if ((*curr)->value == APPEND)
		handle_append_parser(fds, &fds[4], curr, env);
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
