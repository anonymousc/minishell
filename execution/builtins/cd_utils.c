/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:29:45 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:29:46 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_variable(t_env *env, char *variable_name)
{
	while (env)
	{
		if (ft_strcmp(env->variable, variable_name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env_value(t_env *env, char *variable_name, char *new_value)
{
	t_env	*var;

	var = find_variable(env, variable_name);
	if (var)
		var->value = ft_strdup(new_value);
	else
		return ;
	gc_add(0, var->value);
}

void	update_oldpwd(t_env *env, char *old_pwd)
{
	update_env_value(env, "OLDPWD", old_pwd);
}

void	update_pwd(t_env *env)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * PATH_MAX);
	gc_add(0, cwd);
	if (getcwd(cwd, PATH_MAX) != NULL)
		update_env_value(env, "PWD", cwd);
	else
		perror("getcwd error");
}

int	handle_single_argument(t_env *env, t_execution *exec)
{
	if (!exec->cmd[1])
	{
		if (chdir(find_env_variable2(env, "HOME")) != 0)
			perror("cd : HOME not set");
		update_oldpwd(env, find_env_variable2(env, "#PWD"));
		update_pwd(env);
		return (1);
	}
	chdir(find_env_variable2(env, "#PWD"));
	return (0);
}
