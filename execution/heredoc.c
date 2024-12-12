#include "minishell.h"

static char	*namegen(void)
{
	int		fd;
	int		i;
	char	*file;
	char	*buf;
	int		j;

	fd = open("/dev/random", O_RDONLY);
	i = 0;
	file = malloc(11);
	gc_add(0, file);
	buf = malloc(1);
	gc_add(0, buf);
	j = 0;
	while (i < 10)
	{
		read(fd, buf, 1);
		if (ft_isascii(*buf))
			file[j++] = *buf;
		i++;
	}
	file[j] = '\0';
	close(fd);
	return (file);
}

static char	*randgen(char *s)
{
	char	*pathname;

	pathname = "/tmp/";
	s = ft_strjoin(pathname, namegen());
	return (s);
}

static int	file_to_write_on(char **filename)
{
	char	*path;
	int		fd;

	path = randgen(*filename);
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	*filename = path;
	gc_add(0, path);
	return (fd);
}

char	*check_if_expandable(int *check, char *line, t_env *env)
{
	if (*check == 0 && ft_strchr(line, '$'))
	{
		line = ft_strjoin2(before_dollar_word(line), expander(ft_strchr(line,
						'$'), env));
		if (!line)
		{
			line = ft_strdup("");
			gc_add(0, line);
		}
	}
	return (line);
}

void	fork_herdoc(char *delim, int *fd, t_env *env, int *check)
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		signal(SIGINT, sig_heredoc);
		line = readline(">");
		if (!line)
		{
			ft_printf(2, "warning: here-doc delimited by end-of-file\n");
			break ;
		}
		if (!ft_strncmp(delim, line, ft_strlen(delim) + 1))
			break ;
		line = check_if_expandable(check, line, env);
		ft_printf(*fd, "%s\n", line);
		gc_add(0, line);
	}
	exit_minishell(0);
}

void	here_doc_child(char *delim, int *fd1, t_env *env)
{
	int		fd;
	char	*filename;
	int		pid;
	int		check;

	check = check_in_db_or_sq(delim);
	if (check)
	{
		delim = remove_quotes(delim);
		gc_add(0, delim);
	}
	filename = NULL;
	fd = file_to_write_on(&filename);
	pid = fork();
	if (pid == 0)
		fork_herdoc(delim, &fd, env, &check);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	close(fd);
	fd = open(filename, O_RDONLY);
	*fd1 = fd;
}

int	here_doc(t_token **final, t_env *env)
{
	int		hc;
	t_token	*curr;
	t_token	*herecount;
	int		fd;

	hc = 0;
	curr = *final;
	herecount = curr;
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
	signal(SIGINT, sig_handler1);
	here_doc_child(curr->next->data, &fd, env);
	return (fd);
}
