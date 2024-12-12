/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:17 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 21:30:36 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*duplicate_pwd(t_env *env)
{
	char	*secure_value;
	char	*lekher;
	char	*secure_pwd;

	secure_value = find_env_variable2(env, "PWD");
	secure_pwd = ft_strdup("#PWD=");
	gc_add(0, secure_pwd);
	lekher = ft_strjoin2(secure_pwd, secure_value);
	gc_add(0, lekher);
	return (lekher);
}

char	*stop_after_delim(char *s, char spec)
{
	int		i;
	char	*data;

	i = 0;
	while (s[i] && s[i] != spec)
	{
		i++;
	}
	data = malloc(i + 1);
	gc_add(0, data);
	i = 0;
	while (s[i] && s[i] != spec)
	{
		data[i] = s[i];
		i++;
	}
	data[i] = '\0';
	return (data);
}

int	process_export_arg(t_env *env, char *arg)
{
	char	*equal;
	char	*plus;

	equal = strchr(arg, '=');
	plus = strchr(arg, '+');
	if (!equal)
		return (export_without_value(env, arg));
	else
		return (export_with_value(env, arg, equal, plus));
}

t_env	*find_env_variable(t_env *env, char *varname)
{
	while (env)
	{
		if (ft_strcmp(env->variable, varname) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

t_env	*creat_env_var(char *varname, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	gc_add(0, new_var);
	new_var->variable = varname;
	new_var->value = value;
	new_var->next = NULL;
	return (new_var);
}
