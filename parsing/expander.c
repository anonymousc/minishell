#include "minishell.h"

int check_in_db_or_sq(char *s)
{
	int dq = 0;
	int sq = 0;

	int i = 0;
	while (s[i])
	{
		if (s[i] == '"' && !sq)
			dq = 1;
		if (s[i] == '\'' && !dq)
			sq = 1;
		i++;
	}
	if (dq)
		return 2;
	if (sq)
		return 1;
	return 0;
}
char	*before_dollar_word(char	*str)
{
	int i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 0)
		return (NULL);
	word = (char *)malloc(i + 1);
	word[i] = 0;
	ft_strncpy(word,str, i);
	return (word);
}

char *find_env_variable2 (t_env *env, char *varname)
{
    while (env)
    {
        if (env->variable && ft_strcmp(env->variable, varname) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
    return (NULL);
}

char *handle_exit_status(char *tmp, t_env *envp)
{
	char *before_dollar;
	char *exit;
	char *ref;

	exit = ft_itoa(exit_status);
	gc_add(0, exit , NULL);
	before_dollar = before_dollar_word(tmp + 1);
	gc_add(0 , before_dollar , NULL);
	exit = ft_strjoin2(exit, before_dollar);
	ref = ft_strjoin2(exit, expander(tmp + ft_strlen(before_dollar) + 1, envp));
	gc_add(0, exit , NULL);
	gc_add(0, ref , NULL);
	return (ref);
}
char *unexpandable_word(char **tmp , char *expanded_word)
{
	char *before_dollar;

	before_dollar = before_dollar_word(*tmp);
	gc_add(0 , before_dollar , NULL);
	while (**tmp && **tmp != '$')
		(*tmp)++;
	expanded_word = ft_strjoin2(expanded_word, before_dollar);
	gc_add(0, expanded_word, NULL);
	return (expanded_word);
}
char *copy_to_use(char *tmp,char *expansion , t_env *envp)
{
	char *to_expand;
	int len;

	len = tmp - expansion;
	to_expand = malloc (len + 1);
	gc_add(0 , to_expand, NULL);
	ft_strncpy(to_expand, expansion, len);
	to_expand[len] = '\0';
	return (find_env_variable2(envp , to_expand));

}
char *expander(char *expansion, t_env *envp)
{
	char *before_dollar;
	char *expanded_word;
	char *tmp;
	char *ref;

	before_dollar = NULL;
	if (!expansion || *expansion != '$')
		return (NULL);
	expansion = expansion + 1;
	tmp = expansion;
	if (tmp && *tmp == '?')
		return(handle_exit_status(tmp , envp));
	if (*tmp)
		tmp++;
	while(tmp && *tmp && ft_isalnum(*tmp))
		tmp++;
	expanded_word = copy_to_use(tmp , expansion, envp);
	if (*tmp && *tmp != '$')
		expanded_word = unexpandable_word(&tmp, expanded_word);
	ref = ft_strjoin2(expanded_word, expander(tmp, envp));
	gc_add(0 , ref , NULL);
	return (ref);
}

t_token *make_token_list(char **split)
{
	t_token *head = NULL;
	t_token *new_token = NULL;
	t_token *curr = NULL;

	int i = 0;
	while (split && split[i])
	{
		new_token = malloc (sizeof(t_token));
		gc_add(0, new_token, NULL);
		new_token->data = ft_strdup(split[i]);
		gc_add(0, new_token->data, NULL);
		new_token->value = WORD;
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			curr->next = new_token;	
		curr = new_token;
		i++;
	}
	return head;
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
t_token *make_token_list2(char **split)
{
	t_token *head = NULL;
	t_token *new_token = NULL;
	t_token *curr = NULL;

	int i = 0;
	while (split && split[i])
	{
		new_token = malloc (sizeof(t_token));
		new_token->data = ft_strdup(split[i]);
		gc_add(0, new_token->data, NULL);
		new_token->value = get_token(split[i]);
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			curr->next = new_token;	
		curr = new_token;
		i++;
	}
	return head;
}
char **token_to_char(t_token *list)
{
	char **split = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	int i = 0;
	while (list)
	{
		split[i] = list->data;
		i++;
		list = list->next;
	}
	split[i] = NULL;
	return split;
}
void extra_sanitize(t_token **head)
{
    t_token* current = *head;
    t_token* tmp;

    while (current && current->next) 
	{
        if (current->value == WORD && !(*current->data)) 
		{
            tmp = current;
            current = current->next;

            if (tmp == *head) 
                *head = current;
			else 
			{
                t_token* prev = *head;
                while (prev && prev->next != tmp) 
                    prev = prev->next;
                if (prev) 
                    prev->next = current;
            }
			gc_add(0 , tmp , NULL);
		} 
		else 
            current = current->next;
    }
}
static size_t	count_words(char *str)
{
	int		is_word;
	size_t	counter;

	counter = 0;
	is_word = 0;
	while (*str)
	{
		if (*str == is_space_delta(*str))
			is_word = 0;
		else
		{
			if (is_word == 0)
			{
				is_word = 1;
				counter++;
			}
		}
		str++;
	}
	return (counter);
}

static char	*allocate(char **s)
{
	char	*word;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != is_space_delta((*s)[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while ((*s)[i] && (*s)[i] != is_space_delta((*s)[i]))
	{
		word[i] = (*s)[i];
		i++;
	}
	word[i] = '\0';
	*s += i + 1;
	return (word);
}

char	**ft_split_expander(char *s)
{
	char	**splitted;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s);
	splitted = (char **)malloc(sizeof(char *) * (words + 1));
	if (!splitted)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == is_space_delta(*s))
			s++;
		if (*s && *s != is_space_delta(*s))
			splitted[i] = allocate(&s);
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

static void	handle_dollar_expansion(t_token *curr, t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (curr->data[i])
	{
		if (curr->data[i] == '$')
		{
			tmp = expander(curr->data + i, env);
			*(curr->data + i) = '\0';
			if (tmp && *tmp)
			{
				curr->data = ft_strjoin(curr->data, tmp);
				gc_add(0, curr->data, NULL);
			}
			else
				*(curr->data + i) = '\0';
		}
		i++;
	}
}

static void	handle_space_expansion(t_token **final, t_token **curr, t_token *prev, char *tmp)
{
	char	**split;
	char	**next;
	t_token	*last;

	split = ft_split_expander(tmp);
	gc_add_double(0, (void **)split, NULL);
	next = token_to_char((*curr)->next);
	gc_add_double(0, (void **)next, NULL);
	if (*final == *curr)
	{
		*final = make_token_list(split);
		*curr = *final;
		while (*curr && (*curr)->next)
			*curr = (*curr)->next;
		(*curr)->next = make_token_list2(next);
	}
	else
	{
		*curr = make_token_list(split);
		last = ft_lstlast(*curr);
		prev->next = *curr;
		last->next = make_token_list2(next);
	}
}
char *ft_strchr_for_space(char *tmp)
{

	size_t			i;
	size_t			len;

	i = 0;
	len = ft_strlen(tmp);
	while (tmp && i <= len)
	{
		if (tmp[i] == is_space_delta(tmp[i]))
			return ((char *)(tmp + i));
		else
			i++;
	}
	return (0);
}
static void	expand_token(t_token **final, t_token **curr, t_token *prev, t_env *env)
{
	char	*tmp;
	int		i;

	(*curr)->data = ft_strdup((*curr)->data);
	gc_add(0, (*curr)->data, NULL);
	i = 0;
	while ((*curr)->data[i])
	{
		if ((*curr)->data[i] == '$')
		{
			tmp = expander((*curr)->data + i, env);
			*((*curr)->data + i) = '\0';
			if (tmp && *tmp)
			{
				tmp = ft_strjoin((*curr)->data, tmp);
				gc_add(0, tmp, NULL);
				if (ft_strchr_for_space(tmp))
					handle_space_expansion(final, curr, prev, tmp);
				else
					(*curr)->data = tmp;
			}
			else
				*((*curr)->data + i) = '\0';
		}
		i++;
	}
}

void	expander_final(t_token **final, t_env *env)
{
	t_token	*curr;
	t_token	*prev;

	curr = *final;
	prev = NULL;
	while (curr)
	{
		if (curr->value == HEREDOC)
			curr = curr->next->next;
		else if (curr->value == WORD)
		{
			if (check_in_db_or_sq(curr->data) == 2)
				handle_dollar_expansion(curr, env);
			else if (!check_in_db_or_sq(curr->data))
				expand_token(final, &curr, prev, env);
		}
		prev = curr;
		curr = curr->next;
	}
	extra_sanitize(final);
}