/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:26:25 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/11 22:40:20 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*before_dollar_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 0)
		return (NULL);
	word = (char *)malloc(i + 1);
	word[i] = 0;
	ft_strncpy(word, str, i);
	return (word);
}

char	*find_env_variable2(t_env *env, char *varname)
{
	while (env)
	{
		if (env->variable && ft_strcmp(env->variable, varname) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return ("");
}

t_token	*make_token_list(char **split)
{
	t_token	*head;
	t_token	*new_token;
	t_token	*curr;
	int		i;

	head = NULL;
	new_token = NULL;
	curr = NULL;
	i = 0;
	while (split && split[i])
	{
		new_token = malloc(sizeof(t_token));
		gc_add(0, new_token);
		new_token->data = ft_strdup(split[i]);
		gc_add(0, new_token->data);
		new_token->value = WORD;
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			curr->next = new_token;
		curr = new_token;
		i++;
	}
	return (head);
}

t_token	*ft_lstlast(t_token *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_lstsize(t_token *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}
