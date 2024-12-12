#include "minishell.h"

void	builtins_pipe(t_execution *curr, char **env, t_env **env1, int *flag)
{
	if (*flag == 1)
	{
		if (curr->fds[0] != 1)
		{
			dup2(STDOUT_FILENO, curr->fds[0]);
			close(STDOUT_FILENO);
		}
		if (curr->fds[2] != 1)
		{
			dup2(STDOUT_FILENO, curr->fds[2]);
			close(STDOUT_FILENO);
		}
	}
	g_exit_status = execute_builtins(curr, env1, env);
	return (exit_minishell(0), (void)0);
}
void	ft_execve(t_execution *curr, char **env)
{
	char	*fullcmd;
		struct stat data;

	if (check_builtins(curr))
		exit_minishell(0);
	if (curr->cmd )
	{
		fullcmd = find_path(curr->cmd[0], env);
		if (stat(fullcmd, &data) == 0 && S_ISDIR(data.st_mode))
			return (ft_printf(2, "%s is directory\n", fullcmd),
				exit_minishell(126), (void)0);
		if (!fullcmd || !*fullcmd)
		{
			ft_printf(2, "Command not found: %s\n", curr->cmd[0]);
			exit_minishell(127);
		}
		if (execve(fullcmd, curr->cmd, env) == -1)
			return (perror("minishell"), exit_minishell(126), (void)0);
	}
}

void	parent(int *i, int *cmd_count, int *prev_pipe, int *curr_pipe)
{
	if (*i > 0)
		ft_close(&prev_pipe[0], &prev_pipe[1]);
	if (*i < (*cmd_count) - 1)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}
void	wait_for_children(int *pids, int *cmd_count)
{
	int	tmp1;
	int	i;

	i = -1;
	tmp1 = g_exit_status;
	while (++i < *cmd_count)
		waitpid(pids[i], &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = (char)WEXITSTATUS(g_exit_status);
	if (tmp1 == 130)
		g_exit_status = tmp1;
}
int	prepare_child_process(int *i, int *cmd_count, int *curr_pipe)
{
	signal(SIGINT, sigfork);
	signal(SIGQUIT, sig_handler1);
	if (*i < *cmd_count - 1)
		pipe(curr_pipe);
	return (0);
}
