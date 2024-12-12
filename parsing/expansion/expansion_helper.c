/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:22 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 05:28:36 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_exit_status(char *tmp, t_env *envp)
{
	char	*before_dollar;
	char	*exit;
	char	*ref;

	exit = ft_itoa((unsigned char)g_exit_status);
	gc_add(0, exit);
	before_dollar = before_dollar_word(tmp + 1);
	gc_add(0, before_dollar);
	exit = ft_strjoin2(exit, before_dollar);
	ref = ft_strjoin2(exit, expander(tmp + ft_strlen(before_dollar) + 1, envp));
	gc_add(0, exit);
	gc_add(0, ref);
	return (ref);
}

char	*unexpandable_word(char **tmp, char *expanded_word)
{
	char	*before_dollar;

	before_dollar = before_dollar_word(*tmp);
	gc_add(0, before_dollar);
	while (**tmp && **tmp != '$')
		(*tmp)++;
	expanded_word = ft_strjoin2(expanded_word, before_dollar);
	gc_add(0, expanded_word);
	return (expanded_word);
}

char	*copy_to_use(char *tmp, char *expansion, t_env *envp)
{
	char	*to_expand;
	int		len;

	len = tmp - expansion;
	to_expand = malloc(len + 1);
	gc_add(0, to_expand);
	ft_strncpy(to_expand, expansion, len);
	to_expand[len] = '\0';
	return (find_env_variable2(envp, to_expand));
}

char	*expander(char *expansion, t_env *envp)
{
	char	*before_dollar;
	char	*expanded_word;
	char	*tmp;
	char	*ref;

	before_dollar = NULL;
	if (!expansion || *expansion != '$')
		return (NULL);
	expansion = expansion + 1;
	tmp = expansion;
	if (tmp && *tmp == '?')
		return (handle_exit_status(tmp, envp));
	if (*tmp)
		tmp++;
	while (tmp && *tmp && ft_isalnum(*tmp))
		tmp++;
	expanded_word = copy_to_use(tmp, expansion, envp);
	if (*tmp && *tmp != '$')
		expanded_word = unexpandable_word(&tmp, expanded_word);
	ref = ft_strjoin2(expanded_word, expander(tmp, envp));
	gc_add(0, ref);
	return (ref);
}
