/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:37:17 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 21:01:28 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_path_command(char *cmd)
{
	return (ft_strchr(cmd, '/') || ft_strchr(cmd, '.'));
}

static char	*find_path_variable(char **env)
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

static char	**prepare_paths(char *path_var)
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
		paths[0] = remove_quotes(path_var);
		paths[1] = NULL;
		gc_add(0, paths);
	}
	return (paths);
}

static char	*search_executable_in_paths(char **paths, char *cmd)
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
