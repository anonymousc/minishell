#include "minishell.h"

int checker(char *s)
{
	while (*s)
	{
		if(ft_isalpha(*s))
			return (1);
		s++;
	}
	return (0);
}
void my_exit(t_execution *list)
{
	if(!list->cmd[1])
	{
		printf("exit\n");
		exit_minishell(exit_status);
	}
	if(list->cmd[2])
	{
		ft_printf(2 , "too many arguments\n");
		return ;
	}
	if(list->cmd[1])
	{
		printf("exit\n");
		if(checker(list->cmd[1]))
		{
			ft_printf(2 ,"bash: %s: %s: numeric argument required\n", list->cmd[0] , list->cmd[1]);
			exit_minishell(exit_status);
		}
		exit_minishell(ft_atoi(list->cmd[1]));
	}
}
