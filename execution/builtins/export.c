/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:22 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/13 00:18:10 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_existing_var(t_env *existing, char *value, int is_append)
{
	char	*new_value;

	if (is_append)
	{
		new_value = ft_strjoin(existing->value, value);
		gc_add(0, new_value);
		if (!new_value)
			return (0);
		existing->value = new_value;
	}
	else
	{
		new_value = ft_strdup(value);
		gc_add(0, new_value);
		if (!new_value)
			return (0);
		existing->value = new_value;
	}
	return (1);
}

int	export_with_value(t_env *env, char *arg, char *equal, char *plus)
{
	int		is_append;
	int		name_len;
	char	*var_name;
	char	*value;

	is_append = (plus && plus + 1 == equal);
	if (is_append)
		name_len = plus - arg;
	else
		name_len = equal - arg;
	var_name = malloc(name_len + 1);
	gc_add(0, var_name);
	ft_strncpy(var_name, arg, name_len);
	var_name[name_len] = '\0';
	value = equal + 1;
	if (!handle_existing_var(env, var_name, value, is_append))
		return (0);
	return (1);
}

int	export_without_value(t_env *env, char *arg)
{
	t_env	*existing;
	t_env	*new_var;

	existing = find_env_variable(env, arg);
	if (!existing)
	{
		new_var = creat_env_var(arg, "");
		if (!new_var)
			return (0);
		add_back(&(env), new_var);
	}
	return (1);
}

static int	handle_single_args(char **env_array, int *fd_append, int *fd_out)
{
	int		i;
	char	*data;

	i = 0;
	while (env_array && env_array[i])
	{
		data = ft_strchr(env_array[i], '=');
		if (!data && env_array[i][0] != '#')
			ft_printf(*fd_out, "declare -x %s\n", env_array[i++]);
		if (env_array[i] && env_array[i][0] == '#')
		{
			i++;
			continue ;
		}
		if (env_array[i] && data && *fd_append == 1)
			ft_printf(*fd_out, "declare -x %s=\"%s\"\n",
				stop_after_delim(env_array[i], '='), data + 1);
		else if (env_array[i] && data && *fd_out == 1)
			ft_printf(*fd_append, "declare -x %s=\"%s\"\n",
				stop_after_delim(env_array[i], '='), data + 1);
		if (data)
			i++;
	}
	return (0);
}

int	my_export(t_execution *exec, t_env **env, int fd, int fda)
{
	int		i;
	char	*lekher;
	char	**env_array;
	char	*arg;

	env_array = sort_strings(env_to_arr2(*env), env_size(*env));
	lekher = duplicate_pwd(*env);
	if (!exec)
		return (process_export_arg(*env, lekher), 0);
	if (!exec->cmd[1])
		return (handle_single_args(env_array, &fda, &fd));
	i = 1;
	while (exec->cmd[i])
	{
		arg = exec->cmd[i];
		if (is_valid_identifier(fd, arg) < 0)
			return (1);
		if (!process_export_arg(*env, arg))
			return (1);
		i++;
	}
	return (0);
}
