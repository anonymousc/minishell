#include "minishell.h"

void free_spaces2(t_token **head)
{
    t_token* current;
    t_token* tmp;
    t_token* prev;

    current = *head;
    while (current) 
	{
        if (current->value == WHITESPACE) 
		{
            tmp = current;
            current = current->next;
            if (tmp == *head) 
                *head = current;
			else 
			{
                prev = *head;
                while (prev && prev->next != tmp) 
                    prev = prev->next;
                if (prev) 
                    prev->next = current;
            }
        } 
		else 
            current = current->next;
    }
}
void sanitizer(t_token **fill_line) 
{
	t_token *data;
	t_token *tmp;

	data = *fill_line;
    while (data && (data)->next) 
	{
        if ((data)->value == WORD && (data)->next->value == WORD)
		{
			tmp = data->next;
            (data)->data = ft_strjoin((data)->data, (data)->next->data);
            gc_add(0 , data->data);
            (data)->next = (data)->next->next;
        } 
		else 
            data = (data)->next;
    }
}