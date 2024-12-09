#include "minishell.h"

void my_exit(t_execution *list)
{
	if(!list->cmd[1])
		exit_minishell(exit_status);
	if(list->cmd[2])
	{
		printf("too many arguements\n");
		return ;
	}
	if(list->cmd[1])
	{
		printf("exit\n");
		exit_minishell(ft_atoi(list->cmd[1]));
	}
}