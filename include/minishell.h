/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:32:37 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 22:14:28 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ******** C libraries ******** */

# include "../others/MiniLibc/ft_printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ******** DEFINITIONS ********* */

# define PATH_MAX 4096

/* ****************************** */

/* ********** TYPEDEFS ********** */

typedef struct s_memref
{
	void					*mem_data;
	struct s_memref			*next;
}							t_memref;

typedef struct s_memgroup
{
	int						id;
	t_memref				*mem_refs;
	struct s_memgroup		*next;
}							t_memgroup;

typedef struct s_syntax
{
	int						flag;
	int						cmd_count;
	int						iter;

}							t_syntax;

typedef struct s_quotes
{
	int						len;
	int						j;
	int						i;
	int						in_dquote;
	int						in_squote;
	char					q;
}							t_quotes;

typedef struct s_env
{
	char					*variable;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef enum s_Token
{
	PIPE = 1,
	REDIRECTION_OUT,
	REDIRECTION_IN,
	HEREDOC,
	APPEND,
	WORD,
	WHITESPACE
}							t_Token;

typedef struct s_Tokenization
{
	char					*data;
	t_Token					value;
	struct s_Tokenization	*next;

}							t_token;

typedef struct s_execution
{
	char					**cmd;
	int						*fds;
	int						cmd_len;
	struct s_execution		*next;
}							t_execution;

extern int					g_exit_status;

/* ****************************** */

/***************MINILIBC***********/

// CTYPE

int							ft_isdigit(int c);
int							ft_isalpha(int c);
int							ft_isalnum(int c);
int							ft_isascii(int c);
int							is_space(char c);
int							ft_isdigit(int c);
char						*is_space_veta(char s);
char						is_space_delta(char s);

//////////////////////////////

/////////STRINGS/////////////////

char						*ft_itoa(int n);
size_t						ft_strlen(const char *str);
void						ft_bzero(void *s, size_t n);
void						*ft_calloc(size_t nmemb, size_t size);
void						*ft_memcpy(void *dest, const void *src, size_t n);
void						*ft_memset(void *s, int c, size_t n);
char						**ft_split(char *str, char sep);
char						*ft_strchr(const char *s, int c);
int							ft_strcmp(char *s1, char *s2);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strcpy(char *dest, const char *src);
char						*ft_strncpy(char *dest, char *src, size_t n);
char						*ft_strdup(char *src);
char						*ft_strjoin(char *s, char *s1);
char						*ft_strjoin2(char *s, char *s1);
char						*ft_strnstr(const char *haystack,
								const char *needle, size_t n);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
char						*ft_strndup(char *str, size_t n);
int							ft_atoi(char *nptr);
char						*ft_strchr_for_space(char *tmp);
int							handle_heredoc_redirection(t_execution **exec);
char						*ft_strchr_for_export(const char *s, int c);
//////////////////////////////////////
/* ****************************** */

/**************SIGNALS************/

void						sig_handler(int test);
void						sig_handler1(int test);
void						sig_heredoc(int test);
void						sigfork(int data);

/********************************/

/*  ******** PARSING *********  */
////////////SYNTAX//////////////

char						*check_quotes(char *s);
char						*check_syntax(char *s);
int							check_syntax_extended(t_token **final);
int							check_redir(t_token **final);
int							check_heredoc(t_token **final);
int							check_pipe(t_token **final);

////////////////////////////////

////////////LEXER///////////////

char						*retline(void);
t_Token						get_token(char *str);
int							is_separators(char c);
int							is_quotes(char c);
int							check_is_same_quotes2(char c1, char c2);
char						*quotes_holder(char *s);
char						*quotes_holder2(char *s, int *i);
char						**split_to_lex(char *s);
int							quotes_cout_word(char *s, char q);
size_t						word_delim(char const *s);
int							is_quotes(char c);
char						*ft_strdup_and_inc(char *src, char **s);
char						*split_each_token(char *s, char **str, int *i);

///////////////////////////////

///////////////TOKENIZER///////////

t_token						*ft_lstnew(char *content, t_Token t);
void						ft_lstadd_back(t_token **stacks, t_token *new);
void						tokenization(char **line, t_token **fill_line);

///////////////////////////////

////////////////SANITIZATION_INPUT////////////

void						free_spaces2(t_token **head);
void						sanitizer(t_token **fill_line);

/////////////////////////////////////////////

//////////////////QUOTESPLAY////////////////

char						is_quote(char c);
int							count_chars_after_removal(char *s);
char						*remove_quotes(char *s);
void						process_quotes(t_token **final);

///////////////////////////////////////////

////////////////////PARSER////////////////

int							if_redir(t_token **curr);
int							handle_input_redirection_parser(t_token **curr,
								int *fd_out, int *fd_append, t_env *env);
void						ft_lstadd_back_exec(t_execution **stacks,
								t_execution *new);
t_execution					*ft_lstnew_exec(int *fds, char **cmd, int cmdlen);
int							count_cmds(t_token **data);
int							cmd_len(char **cmd);
void						for_execute(t_token **final, t_execution **data,
								t_env *env);
int							handle_output_redirection_parser(t_token **curr,
								int *fflag, int *dflag);
void						handle_append_parser(int *fds, int *fflag,
								t_token **curr, t_env *env);
void						handle_heredoc_parser(int *fd_heredoc,
								t_token **curr, t_env *env);
t_execution					*process_command_tokens(t_token **curr, t_env *env);
void						handle_redirs(int *fds, t_token **curr, t_env *env);
char						**init_cmd_array(int word_count);
int							count_words1(t_token *tokens);
int							*init_fds(int *array);
void						init_fd_(int *fd, int *fd2);

/////////////////////////////////////////

////////////////EXPANDER////////////////

int							check_in_db_or_sq(char *s);
char						*before_dollar_word(char *str);
char						*find_env_variable2(t_env *env, char *varname);
char						*expander(char *expansion, t_env *envp);
t_token						*make_token_list(char **split);
int							ft_lstsize(t_token *lst);
t_token						*make_token_list2(char **split);
char						**token_to_char(t_token *list);
void						extra_sanitize(t_token **head);
void						expander_final(t_token **final, t_env *env);
char						*expander_heredoc(char *expansion, t_env *envp);
char						**ft_split_expander(char *s);
t_token						*ft_lstlast(t_token *lst);
int							if_redir_data(t_token *curr);

/////////////////////////////////////////

/******************************/

/************OTHERS**********/

// ENV

t_env						*make_env(char **env_original);
void						add_back(t_env **envir, t_env *var);
t_env						*get_last(t_env *envir);
int							env_size(t_env *env);

//////////

/******************************/

/************EXEC***********/

void						ft_close(int *fd1, int *fd2);
int							ft_cmd_count(t_execution *curr);
int							redirect_io(t_execution **exec, int *flag);
int							validate_command(char *cmd);
char						*find_path(char *cmd, char **env);
char						**env_to_arr2(t_env *env);
void						execute_bins(t_execution **exec, char **env,
								t_env **env1);
//////////////HEREDOC/////////////

char						*namegen(void);
char						*randgen(char *s);
int							file_to_write_on(char **filename);
void						here_doc_child(char *delim, int *fd1, t_env *env);
int							here_doc(t_token **final, t_env *env);

///////////////////////////////////

//////////////BUITLINS/////////////

void						update_env_value(t_env *env, char *variable_name,
								char *new_value);
t_env						*find_variable(t_env *env, char *variable_name);
int							my_export(t_execution *exec, t_env **env, int fd,
								int fda);
int							my_cd(t_execution *exec, t_env *env);
int							my_pwd(int fd, int fda, t_env *env);
int							my_exit(t_execution *list);
int							my_unset(t_execution **exec, t_env **env);
int							my_env(int fd, int fda, t_env **env);
int							my_echo(int fd, int fda, int ac, char **av);
int							execute_builtins(t_execution *exec, t_env **env,
								char **envs);
int							check_builtins(t_execution *exec);
void						update_oldpwd(t_env *env, char *old_pwd);
void						update_pwd(t_env *env);
int							handle_single_argument(t_env *env,
								t_execution *exec);
void						swap(char **s1, char **s2);
char						**sort_strings(char **str, int len);
int							handle_existing_var(t_env *env, char *var_name,
								char *value, int is_append);
int							is_valid_identifier(int fd, char *arg);
char						*stop_after_delim(char *s, char spec);
t_env						*find_env_variable(t_env *env, char *varname);
t_env						*creat_env_var(char *varname, char *value);
char						*duplicate_pwd(t_env *env);
int							process_export_arg(t_env *env, char *arg);
int							setup_input_redirection(int *i, int *prev_pipe);
int							setup_output_redirection(int *i, int *cmd_count,
								int *curr_pipe, int *flag);
void						builtins_pipe(t_execution *curr, char **env,
								t_env **env1, int *flag);
void						ft_execve(t_execution *curr, char **env);
void						parent(int *i, int *cmd_count, int *prev_pipe,
								int *curr_pipe);
void						wait_for_children(int *pids, int *cmd_count);
int							prepare_child_process(int *i, int *cmd_count,
								int *curr_pipe);
int							export_with_value(t_env *env, char *arg,
								char *equal, char *plus);
int							export_without_value(t_env *env, char *arg);
int							update_existing_var(t_env *existing, char *value,
								int is_append);

///////////////////////////////////

/***************************/

/**** GARBAGE_COLLECTOR ******/

t_memgroup					**gc_get_memgroups(void);
t_memgroup					*gc_create_mem_group(int id);
t_memgroup					*gc_get_specific_memgroup(int id);
t_memref					**gc_get_memrefs(int id);
void						gc_free_memrefs(t_memref *mem_ref);
void						gc_free_specific_memref(t_memref **mem_ref_head,
								t_memref *mem_ref_to_free);
void						gc_add(int mem_group_id, void *mem);
void						gc_add_double(int mem_group_id, void **mem);
void						gc_free_memgrp(int mem_group_id);
void						gc_free_all(void);
void						exit_minishell(int exit_code);

/* **************************** */

#endif