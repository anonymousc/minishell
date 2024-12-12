/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:38:48 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:38:49 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int test)
{
	(void)test;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
	return ;
}

void	sig_handler1(int test)
{
	(void)test;
	g_exit_status = 131;
	printf("\n");
	return ;
}

void	sig_heredoc(int test)
{
	(void)test;
	printf("\n");
	exit_minishell(130);
}

void	sigfork(int data)
{
	(void)data;
	g_exit_status = 130;
	printf("\n");
}
