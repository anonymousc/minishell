#include "minishell.h"

static char *namegen()
{
    int fd = open("/dev/random" , O_RDONLY);
    int i = 0;
    char *file = malloc(11);
    gc_add(0 , file, NULL);
    char *buf = malloc (1);
    gc_add(0 , buf, NULL);
    int j = 0;
    while (i < 10)
    {
        read(fd, buf, 1);
        if (ft_isascii(*buf))
        {
            file[j] = *buf;
            j++;
        }
        i++;
    }
    file[j] = '\0';
    close(fd);
    return file;
}

static char *randgen(char *s)
{
    char *pathname = "/tmp/";

    s = ft_strjoin(pathname, namegen());
    return s;
}

static int file_to_write_on(char **filename)
{
    char *path = randgen(*filename);
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
    *filename = path;
    gc_add(0 ,path, NULL);
    return fd;
}

 char *expander_heredoc(char *expansion, t_env *envp)
{
	char *before_dollar;
	char *expanded_word;
	char *tmp;
	char *exit;

	before_dollar = NULL;
	if (!expansion || *expansion != '$')
		return (expansion);
	expansion = expansion + 1;
	tmp = expansion;
	if (tmp && *tmp == '?')
	{
		exit = ft_itoa(exit_status);
		before_dollar = before_dollar_word(tmp + 1);
		exit = ft_strjoin2(exit, before_dollar);
		return(ft_strjoin2(exit, expander(tmp + ft_strlen(before_dollar) + 1, envp)));
	}
	if (*tmp)
		tmp++;
	while(tmp && *tmp && ft_isalnum(*tmp))
		tmp++;
	int l = tmp - expansion;
	char *to_expand = malloc (l + 1);
	ft_strncpy(to_expand, expansion, l);
	to_expand[l] = '\0';
	expanded_word = find_env_variable2(envp , to_expand);
	if (*tmp && *tmp != '$')
	{
		before_dollar = before_dollar_word(tmp);
		while (*tmp && *tmp != '$')
			tmp++;
		expanded_word = ft_strjoin2(expanded_word, before_dollar);
	}
	return (ft_strjoin2(expanded_word, expander(tmp, envp)));
}



void here_doc_child(t_token *final , int *fd1 ,t_env *env)
{
    t_token *curr = final;
    int fd;
    char *line;
    char *filename = NULL;
    fd = file_to_write_on(&filename);
    char *delim = curr->next->data;
    printf("delim is == %s\n", delim);
    int check = check_in_db_or_sq(delim);
    if(check)
    {
        delim = remove_quotes(delim);
        gc_add(0,delim, NULL);
    }
    int pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, sig_heredoc);
        while (1)   
        {
            line = readline(">");
            if(!line)
            {
                ft_printf(2, "warning: here-doc delimited by end-of-file\n");
                break;
            }
            if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
                break;
            if(check == 0 && ft_strchr(line, '$'))
            {
                char *before_dollar = before_dollar_word(line);
                line = ft_strchr(line, '$');
                line = ft_strjoin2(before_dollar, expander(line, env));
                if(!line)
                {
                    line = ft_strdup("");
                    gc_add(0 , line , NULL);
                }
            }
            ft_printf(fd, "%s\n", line);
            gc_add(0 , line , NULL);
        }
        exit_minishell(0);
    }
    waitpid (pid, &exit_status, 0);
    if (WIFEXITED(exit_status))
        exit_status = WEXITSTATUS(exit_status);
    close(fd);
    fd = open(filename, O_RDONLY);
    *fd1 = fd;
}

int here_doc(t_token **final ,t_env *env)
{
    int hc = 0;
    t_token *curr = *final;
    t_token *herecount = curr;
	int fd;

    fd = 0;
    while (herecount)
    {
        if (herecount->value == HEREDOC)
            hc++;
        if (hc >= 17)
        {
            ft_printf(2, "minishell: maximum here-document count exceeded\n");
            exit_minishell(2);
        }
        herecount = herecount->next;
    }
    here_doc_child(curr , &fd ,env);
	return (fd);
}