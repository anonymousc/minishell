#include "minishell.h"

int exit_status;

int parsing(t_env **env ,t_execution **data)
{
	char *readline;
	char **line;
	t_token  **final;

	line = NULL;
	final = (t_token  **)malloc(sizeof(t_token *));
	gc_add(0 , final , NULL);
	readline = retline();
	if(!readline)
		return 1;
	line = split_to_lex(readline);
	tokenization(line , final);
	gc_add_double(0 , (void **)line, NULL);
	sanitizer(final);
	expander_final(final , *env);
	process_quotes(final);
	if (check_syntax_extended(final))
		return (exit_status = 2, 1);
	free_spaces2(final);
	for_execute(final , data , *env);
	return 0;
}

void execution(t_execution **data ,char **envp ,t_env **env)
{
	execute_bins(data, envp , env);
}

void exit_minishell(int exit_code)
{
	gc_free_all();
	exit(exit_code);
}

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_execution **data;
	t_env *env;

	env = NULL;
	while(1)
	{
		data = (t_execution  **)malloc(sizeof(t_execution  *));
		gc_add(0, data, NULL);
		if (!env)
			env = make_env(envp);
		if(!data || parsing(&env, data))
			continue;
		my_export(NULL, &env, 0, 0);
		execution( data, envp, &env);
		
	}
}
