/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:29:59 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 22:23:20 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_newline(int ac, char **av, int *start_i)
{
	bool	new_line;
	int		i;

	new_line = true;
	*start_i = 1;
	while (*start_i < ac && av[*start_i][0] == '-')
	{
		i = 1;
		while (av[*start_i][i] == 'n')
		{
			new_line = false;
			i++;
		}
		if (av[*start_i][i] != '\0')
		{
			break ;
		}
		(*start_i)++;
	}
	return (new_line);
}

int	print_helper(int fd, int fda)
{
	if (fda == 1)
		ft_printf(fd, "\n");
	else
		ft_printf(fda, "\n");
	return (0);
}

int	my_echo(int fd, int fda, int ac, char **av)
{
	int		start_i;
	bool	new_line;

	if (!av[1])
		return (print_helper(fd, fda));
	new_line = check_newline(ac, av, &start_i);
	while (av[start_i] && start_i < ac)
	{
		if (fda == 1)
			ft_printf(fd, "%s", av[start_i]);
		else
			ft_printf(fda, "%s", av[start_i]);
		if (start_i < ac - 1)
		{
			if (fda == 1)
				ft_printf(fd, " ");
			else
				ft_printf(fda, " ");
		}
		start_i++;
	}
	if (new_line)
		print_helper(fd, fda);
	return (0);
}
