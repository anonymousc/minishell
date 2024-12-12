/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:27:06 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 05:24:38 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

void	exit_minishell(int exit_code)
{
	gc_free_all();
	exit(exit_code);
}

int	parsing(t_env **env, t_execution **data)
{
	char	*readline;
	char	**line;
	t_token	**final;

	line = NULL;
	final = (t_token **)malloc(sizeof(t_token *));
	gc_add(0, final);
	readline = retline();
	if (!readline)
		return (1);
	line = split_to_lex(readline);
	tokenization(line, final);
	sanitizer(final);
	if (check_syntax_extended(final))
		return (g_exit_status = 2, 1);
	expander_final(final, *env);
	process_quotes(final);
	free_spaces2(final);
	for_execute(final, data, *env);
	return (0);
}

void	execution(t_execution **data, char **envp, t_env **env)
{
	execute_bins(data, envp, env);
}

int	main(int ac, char **av, char **envp)
{
	t_execution	**data;
	t_env		*env;

	(void)ac;
	(void)av;
	env = NULL;
	while (1)
	{
		data = (t_execution **)malloc(sizeof(t_execution *));
		gc_add(0, data);
		if (!env)
			env = make_env(envp);
		if (!data || parsing(&env, data))
			continue ;
		my_export(NULL, &env, 0, 0);
		execution(data, envp, &env);
	}
}
