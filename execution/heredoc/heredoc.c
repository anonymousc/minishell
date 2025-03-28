/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:55 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:38:35 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_if_expandable(int *check, char *line, t_env *env)
{
	if (*check == 0 && ft_strchr(line, '$'))
	{
		line = ft_strjoin2(before_dollar_word(line), expander(ft_strchr(line,
						'$'), env));
		if (!line)
		{
			line = ft_strdup("");
			gc_add(0, line);
		}
	}
	return (line);
}

void	fork_herdoc(char *delim, int *fd, t_env *env, int *check)
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		signal(SIGINT, sig_heredoc);
		line = readline(">");
		if (!line)
		{
			ft_printf(2, "warning: here-doc delimited by end-of-file\n");
			break ;
		}
		if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
			break ;
		line = check_if_expandable(check, line, env);
		ft_printf(*fd, "%s\n", line);
		gc_add(0, line);
	}
	exit_minishell(0);
}

void	here_doc_child(char *delim, int *fd1, t_env *env)
{
	int		fd;
	char	*filename;
	int		pid;
	int		check;

	check = check_in_db_or_sq(delim);
	if (check)
	{
		delim = remove_quotes(delim);
		gc_add(0, delim);
	}
	filename = NULL;
	fd = file_to_write_on(&filename);
	pid = fork();
	if (pid == 0)
		fork_herdoc(delim, &fd, env, &check);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	close(fd);
	fd = open(filename, O_RDONLY);
	*fd1 = fd;
}

int	here_doc(t_token **final, t_env *env)
{
	int		hc;
	t_token	*curr;
	t_token	*herecount;
	int		fd;

	hc = 0;
	curr = *final;
	herecount = curr;
	fd = 0;
	while (herecount)
	{
		if (herecount->value == HEREDOC)
			hc++;
		if (hc >= 17)
		{
			ft_printf(2, "minishell: maximum here-document count exceeded\n");
			exit_minishell(2);
		}
		herecount = herecount->next;
	}
	signal(SIGINT, sig_handler1);
	here_doc_child(curr->next->data, &fd, env);
	return (fd);
}
