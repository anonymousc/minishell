#include "minishell.h"

char is_quote(char c) 
{
    if (c == '\'') return '\'';
    if (c == '"') return '"';
    return 0;
}

int count_chars_after_removal(char *s) 
{
    int count = 0;
    int in_dquote = 0;
    int in_squote = 0;
    
    while (s && *s) 
	{
        char q = is_quote(*s);
        if (q == '"' && !in_squote) 
            in_dquote = !in_dquote;
		else if (q == '\'' && !in_dquote) 
            in_squote = !in_squote;
		else 
            count++;
        s++;
    }
    return count;
}

char *remove_quotes(char *s) 
{    
    int len = count_chars_after_removal(s);
    char *result = malloc(sizeof(char) * (len + 1));
    int j = 0;
	int i = 0; 
    int in_dquote = 0;
    int in_squote = 0;
    
    while (s && s[i]) 
	{
        char q = is_quote(s[i]);
        if (q == '"' && !in_squote) 
            in_dquote = !in_dquote;
		else if (q == '\'' && !in_dquote) 
            in_squote = !in_squote;
		else 
            result[j++] = s[i];
		i++;
    }
    result[j] = '\0';
    return result;
}

void process_quotes(t_token **final)
{
    t_token *curr = *final;
    char *processed;
    while (curr) 
	{
		if(curr->value == HEREDOC && curr->next->next)
			curr = curr->next->next;
        else if (curr->value == WORD) 
		{
            processed = remove_quotes(curr->data);
			gc_add(0, processed , NULL);
            curr->data = processed;
        }
        curr = curr->next;
    }
}