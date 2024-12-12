/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:25 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:30:26 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(int fd, int fda, t_env *env)
{
	char	*s;

	s = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!s)
		return (1);
	if (!getcwd(s, PATH_MAX))
	{
		if (fda == 1)
			ft_printf(fd, "%s\n", find_env_variable2(env, "#PWD"));
		else
			ft_printf(fda, "%s\n", find_env_variable2(env, "#PWD"));
		free(s);
		return (1);
	}
	if (fda == 1)
		ft_printf(fd, "%s\n", getcwd(s, PATH_MAX));
	else
		ft_printf(fda, "%s\n", getcwd(s, PATH_MAX));
	free(s);
	return (0);
}
