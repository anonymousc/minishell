/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:45 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/13 00:04:55 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_redir(t_token **curr)
{
	return ((*curr)->value == REDIRECTION_IN
		|| (*curr)->value == REDIRECTION_OUT || (*curr)->value == APPEND
		|| (*curr)->value == HEREDOC);
}

int	handle_input_redirection_parser(t_token **curr, int *fds, int *fflag,
		t_env *env)
{
	int	fd_in;

	fd_in = 0;
	if ((*curr)->next && (*curr)->next->data)
	{
		if (ft_strchr((*curr)->next->data, '$'))
		{
			(*curr)->next->data = ambugious_redirection((*curr)->next->data,
					env);
			if (ft_strchr_for_space((*curr)->next->data)
				|| !(*(*curr)->next->data))
				fd_in = -3;
		}
		if (fd_in != -3)
			fd_in = open((*curr)->next->data, O_RDONLY, 0444);
		if (fd_in == -1)
			init_fd_(&fds[0], &fds[2]);
		else if (!ft_strncmp((*curr)->next->data, "/dev/stdin",
				ft_strlen("/dev/stdin")))
			fd_in--;
		if ((fd_in > 0) && access((*curr)->next->data, R_OK | W_OK) == -1)
			*fflag = 1;
		*curr = (*curr)->next;
	}
	return (fd_in);
}

int	handle_output_redirection_parser(t_token **curr, int *fflag, int *dflag,
		t_env *env)
{
	struct stat	dstat;
	int			fd_out;

	fd_out = 1;
	if ((*curr)->next && (*curr)->next->data)
	{
		if (ft_strchr((*curr)->next->data, '$'))
		{
			(*curr)->next->data = ambugious_redirection((*curr)->next->data,
					env);
			if (!(*(*curr)->next->data)
				|| !ft_strchr_for_space((*curr)->next->data))
				fd_out = -3;
		}
		if (stat((*curr)->next->data, &dstat) > -1)
			if (S_ISDIR(dstat.st_mode))
				*dflag = 1;
		if (*(*curr)->next->data)
			check_validity((*curr)->next->data, &fd_out, fflag);
		*curr = (*curr)->next;
	}
	return (fd_out);
}

void	handle_append_parser(int *fds, int *fflag, t_token **curr, t_env *env)
{
	if ((*curr)->next && (*curr)->next->data)
	{
		if (ft_strchr((*curr)->next->data, '$'))
		{
			(*curr)->next->data = ambugious_redirection((*curr)->next->data,
					env);
			if (!(*(*curr)->next->data)
				|| ft_strchr_for_space((*curr)->next->data))
			{
				fds[2] = -3;
			}
		}
		if (fds[0] != 1 || fds[2] == 1 || fds[2] != -3)
			fds[0] = open((*curr)->next->data, O_CREAT | O_RDWR | O_APPEND,
					0666);
		else if (fds[2] != -3)
			fds[2] = open((*curr)->next->data, O_CREAT | O_RDWR | O_APPEND,
					0666);
		if (access((*curr)->next->data, R_OK | W_OK) == -1)
			*fflag = 1;
		*curr = (*curr)->next;
	}
}

void	handle_heredoc_parser(int *fd_heredoc, t_token **curr, t_env *env)
{
	if ((*curr)->next && (*curr)->next->data)
	{
		*fd_heredoc = here_doc(curr, env);
		*curr = (*curr)->next;
	}
}
