#ifndef MINISHELL_H
#define MINISHELL_H


/* ******** C libraries ******** */

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include "../others/MiniLibc/ft_printf/ft_printf.h"

/* ******** DEFINITIONS ********* */

# define PATH_MAX       4096

/* ****************************** */

/* ********** TYPEDEFS ********** */

typedef struct s_memref
{
	void				*mem_data;
	struct s_memref		*next;
}						t_memref;

typedef struct s_memgroup
{
	int					id;
	t_memref			*mem_refs;
	struct s_memgroup	*next;
}						t_memgroup;

typedef struct	s_syntax
{
	int s_q;
	int d_q;
	int iter;
}				t_syntax;

typedef struct s_env
{
    char *variable;
    char *value;
    struct s_env *next;
} t_env;

typedef enum
{
	PIPE = 1,
	REDIRECTION_OUT,
	REDIRECTION_IN,
	HEREDOC,
	APPEND,
	WORD,
	WHITESPACE

} Token;

typedef	struct	s_Tokenization
{
	char					*data;
	Token					value;
	struct s_Tokenization	*next;

}		t_token;

typedef struct s_execution
{
	char 				**cmd;
	int					*fds;
	int					cmd_len;
	struct s_execution	*next;
}					t_execution;

extern int exit_status;

/* ****************************** */




/***************MINILIBC***********/

//CTYPE

int		ft_isdigit(int c);
int		ft_isalpha (int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		is_space(char c);
int		ft_isdigit(int c);
char	*is_space_veta(char s);

//////////////////////////////

char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(char *str, char sep);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest , char *src, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s, char *s1);
char	*ft_strjoin2(char *s, char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strndup(char *str, size_t n);
int		ft_atoi(char *nptr);
/* ****************************** */


/**************SIGNALS************/

void sig_handler(int test);
void sig_handler1(int test);
void sig_heredoc(int test);
void sigfork(int data);

/********************************/

/*  ******** PARSING *********  */

////////////LEXER///////////////

char  *retline(void);
Token get_token (char *str);
int	is_separators(char c);
int is_quotes(char c);
int check_is_same_quotes2(char c1, char c2);
char *quotes_holder(char *s);
char *quotes_holder2(char *s, int  *i);
char	**split_to_lex(char *s);

///////////////////////////////

///////////////TOKENIZER///////////

t_token	*ft_lstnew(char *content, Token t);
void	ft_lstadd_back(t_token **stacks, t_token *new);
void	tokenization(char **line , t_token **fill_line);

///////////////////////////////

////////////////SANITIZATION_INPUT////////////

void free_spaces2(t_token **head);
void sanitizer(t_token **fill_line);

/////////////////////////////////////////////

//////////////////QUOTESPLAY////////////////

char is_quote(char c);
int count_chars_after_removal(char *s);
char *remove_quotes(char *s);
void process_quotes(t_token **final);

///////////////////////////////////////////

////////////////////PARSER////////////////

void	ft_lstadd_back_exec(t_execution  **stacks, t_execution  *new);
t_execution  *ft_lstnew_exec(int *fds, char **cmd, int cmdlen);
int count_cmds(t_token **data);
int cmd_len (char **cmd);
void for_execute(t_token **final, t_execution **data, t_env *env);

/////////////////////////////////////////

////////////////EXPANDER////////////////

int check_in_db_or_sq(char *s);
char	*before_dollar_word(char	*str);
char *find_env_variable2(t_env *env, char *varname);
char *expander(char *expansion, t_env *envp);
t_token *make_token_list(char **split);
int	ft_lstsize(t_token *lst);
t_token *make_token_list2(char **split);
char **token_to_char(t_token *list);
void extra_sanitize(t_token **head);
void expander_final(t_token **final ,t_env *env);
char *expander_heredoc(char *expansion, t_env *envp);

/////////////////////////////////////////

/******************************/

char *check_quotes(char *s);
char *check_syntax(char *s);
int check_syntax_extended(t_token **final) ;

/************OTHERS**********/

//ENV

t_env *make_env(char **env_original);
void add_back(t_env **envir, t_env *var);
t_env *get_last(t_env *envir);
int		env_size(t_env *env);

//////////

/******************************/

/************EXEC***********/

void ft_close(int *fd1 , int *fd2);
int ft_cmd_count(t_execution * curr);
int redirect_io(t_execution **exec, int *flag);
char *find_path(char *cmd, char **env);
char **env_to_arr2(t_env *env);
void execute_bins(t_execution **exec, char **env, t_env **env1 );
///HEREDOC

void here_doc_child(t_token *final , int *fd1 ,t_env *env);
int here_doc(t_token **final ,t_env *env);

//////////

///BUITLINS

int my_export(t_execution *exec , t_env **env, int fd, int fda);
int	my_cd(t_execution *exec , t_env *env);
int	my_pwd(int fd, int fda, t_env *env);
void my_exit(t_execution *list);
int my_unset(t_execution **exec, t_env **env);
int my_env(int fd, int fda, t_env **env);
int my_echo (int fd , int fda, int ac, char **av);
int execute_builtins(t_execution *exec  ,t_env **env, char **envs);
int check_builtins(t_execution *exec);

///////////

/***************************/

/**** GARBAGE_COLLECTOR ******/

t_memgroup				**gc_get_memgroups(void);
t_memgroup				*gc_create_mem_group(int id);
t_memgroup				*gc_get_specific_memgroup(int id);
t_memref				**gc_get_memrefs(int id);
void					gc_free_memrefs(t_memref *mem_ref);
void					gc_free_specific_memref(t_memref **mem_ref_head ,t_memref *mem_ref_to_free);
void					*gc_calloc(int mem_group_id, size_t count, size_t size ,t_memref **store_memref);
void					*gc_malloc(int mem_group_id, size_t size ,t_memref **store_memref);
void					gc_add(int mem_group_id, void *mem ,t_memref **store_memref);
void					gc_add_double(int mem_group_id, void **mem,t_memref **store_memref);
void					gc_free_memgrp(int mem_group_id);
void					gc_free_all(void);
void					exit_minishell(int exit_code);

/* **************************** */

#endif