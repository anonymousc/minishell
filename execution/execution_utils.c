#include "minishell.h"

int	ft_cmd_count(t_execution *curr)
{
	t_execution	*temp;
	int			cmd_counter;

	temp = curr;
	cmd_counter = 0;
	while (temp)
	{
		cmd_counter++;
		temp = temp->next;
	}
	return (cmd_counter);
}

void	ft_close(int *fd1, int *fd2)
{
	close(*fd1);
	close(*fd2);
}

int	is_path_command(char *cmd)
{
	return (ft_strchr(cmd, '/') || ft_strchr(cmd, '.'));
}

int	validate_command(char *cmd)
{
	if (!cmd)
		return (0);
	if (!*cmd)
		return (0);
	return (1);
}

char	*find_path_variable(char **env)
{
	int	j;

	j = 0;
	while (env && env[j])
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
			return (env[j] + 5);
		j++;
	}
	return (NULL);
}

char	**prepare_paths(char *path_var)
{
	char	**paths;

	if (ft_strchr(path_var, ':'))
	{
		paths = ft_split(path_var, ':');
		gc_add_double(0, (void **)paths);
	}
	else
	{
		paths = (char **)malloc(2 * sizeof(char *));
		gc_add(0, paths);
		paths[0] = remove_quotes(path_var);
		paths[1] = NULL;
	}
	return (paths);
}

char	*search_executable_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*full_command;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		gc_add(0, full_path);
		full_command = ft_strjoin(full_path, cmd);
		gc_add(0, full_command);
		if (access(full_command, F_OK | X_OK) == 0)
			return (full_command);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	*path_var;
	char	**paths;

	if (!validate_command(cmd))
		return (cmd);
	if (is_path_command(cmd))
	{
		if (!access(cmd, F_OK))
			return (cmd);
		return (NULL);
	}
	path_var = find_path_variable(env);
	if (!path_var)
		return (NULL);
	paths = prepare_paths(path_var);
	return (search_executable_in_paths(paths, cmd));
}
