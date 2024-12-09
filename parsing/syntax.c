#include "minishell.h"

char *check_quotes(char *s)
{
	t_syntax syntax;

	syntax.iter = 0;
	int sq = 0;
	int dq = 0;
	while(s && s[syntax.iter])
	{
		if(s[syntax.iter] == '\'' && !dq)
			sq = !sq;
		if(s[syntax.iter] == '\"' && !sq)
			dq = !dq;
		syntax.iter++;
	}
	if(dq || sq)
		return (printf("minishell: Unclosed Quotes\n"), NULL);
	return(s);
}

char *check_syntax(char *s)
{
	if(!check_quotes(s))
		return (free(s), NULL);
	return (s);
}

t_token *free_spaces (t_token *curr)
{
	while (curr && curr->value == WHITESPACE)
		curr = curr->next;
	return curr;
}

int check_pipe(t_token **final) 
{
    t_token *curr;
	
	curr = *final;
    if (curr && curr->value == PIPE) 
		return (ft_printf(2, "syntax error\n"), 1);	
    while (curr) 
	{
        if (curr->value == PIPE)
		 {
            if (!curr->next || curr->next->value == PIPE)
				return (ft_printf(2, "syntax error\n"), 1);
			curr = curr->next;
			if(curr->value == WHITESPACE)
			{
            	curr = free_spaces(curr);
				if (!curr || curr->value == PIPE) 
                	return (ft_printf(2, "syntax error\n"), 1);
			}
		}
		if(curr)
			curr = curr->next;
    }
    return 0;
}

int check_heredoc(t_token **final)
{
	t_token *curr = *final;
	while (curr)
	{
		if(curr->value == HEREDOC || curr->value == APPEND)
		{
			if (!curr->next || curr->next->value == HEREDOC || curr->next->value == PIPE ||  curr->next->value == APPEND || curr->next->value == REDIRECTION_IN || curr->next->value == REDIRECTION_OUT) 
				return (ft_printf(2, "syntax error\n"), 1);
			curr = curr->next;
			if(curr->value == WHITESPACE)
			{
            	curr = free_spaces(curr);
				if (!curr || curr->value == HEREDOC || curr->value == PIPE ||  curr->value == APPEND || curr->value == REDIRECTION_IN || curr->value == REDIRECTION_OUT) 
                	return (ft_printf(2, "syntax error\n"), 1);
			}
		}
		if(curr)
			curr = curr->next;
	}
	return 0;
}

int check_redir(t_token **final)
 {
	t_token *curr = *final;
	while (curr)
	{
		if(curr->value == REDIRECTION_IN || curr->value == REDIRECTION_OUT)
		{
			if (!curr->next || curr->next->value == HEREDOC || curr->next->value == PIPE ||  curr->next->value == APPEND || curr->next->value == REDIRECTION_OUT || curr->next->value == REDIRECTION_IN) 
				return (ft_printf(2, "syntax error\n"), 1);
			curr = curr->next;
			if(curr->value == WHITESPACE)
			{
            	curr = free_spaces(curr);
				if (!curr || curr->value == HEREDOC || curr->value == PIPE || curr->value == APPEND || curr->value == REDIRECTION_IN || curr->value == REDIRECTION_OUT) 
                	return (ft_printf(2, "syntax error\n"), 1);
			}
		}
		if(curr)
			curr = curr->next;
	}
	return 0;
}

int check_syntax_extended(t_token **final) 
{
    	return (check_heredoc(final) || check_pipe(final) || check_redir(final));
}
