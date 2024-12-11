#include "minishell.h"

int is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

int check_is_same_quotes2(char c1, char c2)
{
	return (c1 == c2);
}

char *quotes_holder(char *s)
{
	char	quote;
	
	quote = (*s)++;
	while (s && *s && !check_is_same_quotes2(*s, quote))
		s++;
	return (s);
}

char *quotes_holder2(char *s, int  *i)
{
	char	quote;
	
	(*i) = 0;
	quote = (*i)++;
	while (s && s[(*i)] && !check_is_same_quotes2(s[(*i)], quote))
		(*i)++;
	return (s);
}


Token get_token (char *str)
{
	if (ft_strnstr(str,"|",1))
		return (PIPE);
	else if (ft_strnstr(str,"<<",2))
		return (HEREDOC);
	else if (ft_strnstr(str , ">>" , 2))
		return (APPEND);
	else if(ft_strnstr(str, ">" , 1))
		return (REDIRECTION_OUT);
	else if(ft_strnstr(str, "<" , 1))
		return(REDIRECTION_IN);
	else if(ft_strnstr(str , " " , 1) || ft_strnstr(str , "\n" , 1) 
	|| ft_strnstr(str , "\v" , 1) || ft_strnstr(str , "\t" , 1) 
	|| ft_strnstr(str , "\r" , 1))
		return (WHITESPACE);
	return WORD;
}

int	is_separators(char c)
{
	if (c == '|' || c == '>' || c == '<' || is_space(c))
		return 1;
	return 0;
}

static size_t	word_delim(char const *s)
{
	size_t		counter;
	int			in_word;
	char const	*p;

	int i = 0;
	counter = 0;
	p = s;
	while (p && *p)
	{
		in_word = 0;
		if (is_quotes(*p))
		{
				p = quotes_holder2((char *)p , &i);
				counter++;
		}
		else if (is_separators(*p) || in_word == 0)
		{
			in_word = 1;
			counter++;
		}
		p++;
	}
	return (counter);
}

static int quotes_cout_word(char *s,char q)
{
	int i = 0 ;
	while (s && s[i] && s[i] != q)
		i++;
	return i;
}
static char	*ft_strdup_and_inc(char *src, char **s)
{
	size_t	i;
	char	*duplicate;

	if (!src)
		return (NULL);
	duplicate = (char *) malloc ((ft_strlen(src) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src[i])
	{
		duplicate[i] = src[i];
		i++;
	}
	duplicate[i] = '\0';
	*s += ft_strlen(src);
	return (duplicate);
}

static char *split_each_token(char *s, char **str , int *i)
{
	Token t;
	t = get_token(s);
	if (t == PIPE)
		str[(*i)] = ft_strdup_and_inc("|", &s);
	else if (t == HEREDOC)
		str[(*i)] = ft_strdup_and_inc("<<", &s);
	else if (t == APPEND)
		str[(*i)] = ft_strdup_and_inc(">>", &s);
	else if (t == REDIRECTION_IN)
		str[(*i)] = ft_strdup_and_inc("<", &s);
	else if (t == REDIRECTION_OUT)
		str[(*i)] = ft_strdup_and_inc(">" , &s);
	else if(t == WHITESPACE)
		str[(*i)] = ft_strdup_and_inc(is_space_veta(*s), &s);
	return (s);
}
static char *qoutes_detailer(char *s , char **str , int *i)
{
	char q = *s;
	str[(*i)] = ft_substr(s,0,quotes_cout_word(s + 1,q) + 2);
	gc_add(0 ,str[(*i)], NULL);
	s += quotes_cout_word(s + 1,q) + 2;
	(*i)++;
	return s;
}

static char *skip_checker(char *s, int *len)
{
	char *start = s;
	while ((*s && !(is_separators(*s) || is_quotes(*s))))
			(s)++;
	*len = s - start;
	return s;
}
static char *isnt_asep(char **str , int *i, int *len, char *start)
{
	str[(*i)] = (char *)malloc(((*len) + 1) * sizeof(char));
	// gc_add(0 , str , NULL);
	ft_memcpy(str[(*i)], start, (*len));
	str[(*i)][(*len)] = '\0';
	return (str[(*i)]);
}

static char	**str_all_fill_v2(char **str, char const *s)
{
	const char		*start;
	int			i;
	int			len;

	i = 0;
	while (s && *s)
	{
		if (is_quotes(*s))
			s = qoutes_detailer((char *)s ,str , &i);
		else if (is_separators(*s))
		{
			s = split_each_token((char *)s , str , &i);
			i++;
		}
		else if (!is_separators(*s))
		{
			start = s;
			s = skip_checker((char *)s, &len);
			str[i++] = isnt_asep(str, &i , &len, (char *)start);
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**split_to_lex(char *s)
{
	char		**str;

	if (!s)
		return (NULL);
	str = malloc((word_delim(s) + 1) * sizeof(char *));
	return (str_all_fill_v2(str,  s));
}