/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:29 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:30:30 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**unset_var(t_execution **exec, char *s, t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	(void)exec;
	curr = *env;
	if (curr && !ft_strcmp(curr->variable, s))
	{
		tmp = curr;
		curr = curr->next;
		*env = curr;
	}
	else
	{
		while (curr && curr->next)
		{
			if (ft_strcmp(curr->next->variable, s) == 0)
			{
				tmp = curr->next;
				curr->next = curr->next->next;
			}
			curr = curr->next;
		}
	}
	return (env);
}

int	my_unset(t_execution **exec, t_env **env)
{
	int	i;

	i = 1;
	while ((*exec)->cmd[i])
	{
		env = unset_var(exec, (*exec)->cmd[i], env);
		i++;
	}
	return (0);
}
