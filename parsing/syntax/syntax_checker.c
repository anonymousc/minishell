/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:25:54 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 22:25:55 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_extended(t_token **final)
{
	return (check_heredoc(final) || check_pipe(final) || check_redir(final));
}

char	*check_quotes(char *s)
{
	t_syntax	syntax;
	int			sq;
	int			dq;

	syntax.iter = 0;
	sq = 0;
	dq = 0;
	while (s && s[syntax.iter])
	{
		if (s[syntax.iter] == '\'' && !dq)
			sq = !sq;
		if (s[syntax.iter] == '\"' && !sq)
			dq = !dq;
		syntax.iter++;
	}
	if (dq || sq)
		return (printf("minishell: Unclosed Quotes\n"), NULL);
	return (s);
}

char	*check_syntax(char *s)
{
	if (!check_quotes(s))
		return (NULL);
	return (s);
}
