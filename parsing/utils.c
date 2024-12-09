#include "minishell.h"

char  *retline(void)
{
		char *line;
		
		signal(SIGINT , sig_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		signal(SIGINT , sig_handler);
		add_history(line);
		if(!line)
			return (printf("exit\n"),exit_minishell(1) ,NULL);
		else if(line)
		{
			line = check_syntax(line);
			if(!line)
				exit_status = 2;	
		}
		return line;
}