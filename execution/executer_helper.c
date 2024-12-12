#include "minishell.h"

int	setup_input_redirection(int *i, int *prev_pipe)
{
	if (*i > 0)
	{
		if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
			return (-1);
		ft_close(&prev_pipe[0], &prev_pipe[1]);
	}
	return (0);
}

int	setup_output_redirection(int *i, int *cmd_count, int *curr_pipe, int *flag)
{
	if (*i < *cmd_count - 1)
	{
		if (*flag == 0 && dup2(curr_pipe[1], STDOUT_FILENO) == -1)
			return (-1);
		ft_close(&curr_pipe[0], &curr_pipe[1]);
	}
	return (0);
}
