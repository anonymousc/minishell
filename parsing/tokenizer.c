#include "minishell.h"

t_token	*ft_lstnew(char *content, Token t)
{	
	t_token  *list;

	list = (t_token *) malloc (sizeof(t_token));
	gc_add(0 , list,NULL);
	list->value = t;
	list->data = content;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back(t_token **stacks, t_token *new)
{
	t_token	*head;

	if (!stacks || !*stacks)
	{
		*stacks = new;
		return ;
	}
	head = *stacks;
	while (head->next)
		head = head->next;
	head->next = new;
	new->next = NULL;
}
void	tokenization(char **line , t_token **fill_line)
{
	int i;
	
	i = -1;
	*fill_line = NULL;
	while (line && line[++i])
		ft_lstadd_back(fill_line , ft_lstnew(line[i] , get_token(line[i])));
}
