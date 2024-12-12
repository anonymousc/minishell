/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_II.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:10 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 22:18:50 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**sort_strings(char **str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				swap(&str[i], &str[j]);
			}
			j++;
		}
		i++;
	}
	return (str);
}

char	*create_env_str(t_env *node)
{
	int		var_len;
	int		val_len;
	int		str_len;
	char	*env_str;

	var_len = ft_strlen(node->variable);
	val_len = ft_strlen(node->value);
	str_len = var_len + val_len + 2;
	env_str = malloc(str_len);
	gc_add(0, env_str);
	if (!env_str)
		return (NULL);
	ft_strcpy(env_str, node->variable);
	if (val_len > 0)
	{
		env_str[var_len] = '=';
		ft_strcpy(env_str + var_len + 1, node->value);
	}
	else
		env_str[var_len] = '\0';
	return (env_str);
}

char	**env_to_arr2(t_env *env)
{
	int		size;
	char	**envir;
	int		i;
	t_env	*current;

	size = env_size(env);
	envir = malloc(sizeof(char *) * (size + 1));
	gc_add(0, envir);
	if (!envir)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		envir[i] = create_env_str(current);
		current = current->next;
		i++;
	}
	envir[i] = NULL;
	return (envir);
}
