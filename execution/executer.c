#include "minishell.h"

void	execute_child_command(t_execution *curr, char **env, t_env **env1,
		int **array, t_syntax *data)
{
	int	*prev_pipe;
	int	*curr_pipe;

	prev_pipe = array[1];
	curr_pipe = array[2];
	if (curr->cmd[0] && curr->cmd[0][0] == '\0')
		exit_minishell(0);
	if (redirect_io(&curr, &data->flag) == -1)
		exit_minishell(1);
	if (setup_input_redirection(&data->iter, prev_pipe) == -1)
		exit_minishell(1);
	if (setup_output_redirection(&data->iter, &data->cmd_count, curr_pipe,
			&data->flag) == -1)
		exit_minishell(1);
	env = env_to_arr2(*env1);
	if (data->cmd_count > 1 && check_builtins(curr))
		builtins_pipe(curr, env, env1, &data->flag);
	else
		ft_execve(curr, env);
}
void	exec_single_builtin(t_execution *curr, char **env, t_env **env1,
		int *cmd_count)
{
	if (*cmd_count == 1 && check_builtins(curr))
	{
		g_exit_status = execute_builtins(curr, env1, env);
		env = env_to_arr2(*env1);
	}
}

int	**init_var_pipes(int **array, t_syntax *data)
{
	array = malloc(sizeof(int *) * 3);
	gc_add(0, array);
	array[0] = malloc(sizeof(pid_t) * data->cmd_count);
	gc_add(0, array[0]);
	array[1] = malloc(sizeof(int) * 2);
	gc_add(0, array[1]);
	array[1][0] = 0;
	array[1][1] = 1;
	array[2] = malloc(sizeof(int) * 2);
	gc_add(0, array[2]);
	return (array);
}
void	execute_bins(t_execution **exec, char **env, t_env **env1)
{
	t_execution	*curr;
	t_syntax	data;
	int			**array;

	array = NULL;
	curr = *exec;
	data.iter = 0;
	data.flag = 0;
	data.cmd_count = ft_cmd_count(curr);
	array = init_var_pipes(array, &data);
	while (curr && data.iter < data.cmd_count)
	{
		exec_single_builtin(curr, env, env1, &data.cmd_count);
		prepare_child_process(&data.iter, &data.cmd_count, array[2]);
		array[0][data.iter] = fork();
		if (array[0][data.iter] == 0)
			execute_child_command(curr, env, env1, array, &data);
		else
			parent(&data.iter, &data.cmd_count, array[1], array[2]);
		curr = curr->next;
		data.iter++;
	}
	wait_for_children(array[0], &data.cmd_count);
}
