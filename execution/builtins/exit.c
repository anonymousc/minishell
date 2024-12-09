#include "minishell.h"

void my_exit(t_execution *list)
{
	if((long long)ft_atoi(list->cmd[1]) < INT_MAX)
	{
		printf("exit\n");
		exit(ft_atoi(list->cmd[1]));
	}
	if(list->cmd[2])
	{
		printf("too many arguements\n");
		return ;
	}
}