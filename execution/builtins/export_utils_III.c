/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_III.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:14 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/13 00:49:14 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_character(int fd, char *arg)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_printf(fd, "%s not a valid identifier\n", arg);
		return (-1);
	}
	return (0);
}

int	is_valid_identifier(int fd, char *arg)
{
	int	i;
	int	plus_count;

	i = 1;
	fd = 2;
	plus_count = 0;
	check_first_character(fd, arg);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
		{
			if (plus_count > 0 || arg[i + 1] != '=')
			{
				ft_printf(fd, "%s not a valid identifier\n", arg);
				return (-1);
			}
			plus_count++;
		}
		else if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (ft_printf(fd, "%s not a valid identifier\n", arg), -1);
		i++;
	}
	return (0);
}

int	handle_existing_var(t_env *env, char *var_name, char *value, int is_append)
{
	t_env	*existing;
	t_env	*new_var;

	existing = find_env_variable(env, var_name);
	if (existing)
	{
		return (update_existing_var(existing, value, is_append));
	}
	else
	{
		if (is_append)
			new_var = creat_env_var(var_name, value);
		else
			new_var = creat_env_var(var_name, value);
		if (!new_var)
			return (0);
		add_back(&(env), new_var);
	}
	return (1);
}
