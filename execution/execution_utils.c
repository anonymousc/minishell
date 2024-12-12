/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:30:50 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:37:53 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	validate_command(char *cmd)
{
	if (!cmd)
		return (0);
	if (!*cmd)
		return (0);
	return (1);
}
