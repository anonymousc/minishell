/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:56 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:03:32 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*retline(void)
{
	char	*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell$ ");
	signal(SIGINT, sig_handler);
	add_history(line);
	if (!line)
		return (printf("exit\n"), exit_minishell(1), NULL);
	else if (line)
	{
		line = check_syntax(line);
		if (!line)
			g_exit_status = 2;
	}
	return (line);
}
