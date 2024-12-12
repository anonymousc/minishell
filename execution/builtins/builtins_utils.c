#include "minishell.h"

int execute_builtins(t_execution *exec  ,t_env **env, char **envs)
{
    (void) envs;
	int ret = 0;

     if(!*(exec->cmd))
            return (0);
	if (ft_strncmp(exec->cmd[0], "echo", 5) == 0)
		ret = my_echo(exec->fds[0], exec->fds[2],  exec->cmd_len, exec->cmd);
	if (ft_strncmp (exec->cmd[0], "cd", 3) == 0)
		ret = my_cd(exec , *env);
	if (ft_strncmp(exec->cmd[0], "pwd", 4) == 0)
		ret = my_pwd(exec->fds[0], exec->fds[2], *env);
	else if (ft_strncmp (exec->cmd[0] , "env", 4) == 0)
		ret = my_env(exec->fds[0],exec->fds[2], env);
	else if (ft_strncmp(exec->cmd[0] , "export", 7) == 0)
        ret = my_export(exec , env, exec->fds[0], exec->fds[2]);
    else if (ft_strncmp (exec->cmd[0] , "unset", 6) == 0)
        ret = my_unset(&exec, env);
    else if(ft_strncmp(exec->cmd[0], "exit" , 5) == 0)
       ret = my_exit(exec);
    return ret;
}
int check_builtins(t_execution *exec)
{
	int ret;

    ret = 0;
     if(!exec->cmd[0])
         return (0);
	if (ft_strncmp(exec->cmd[0], "echo", 5) == 0)
		ret = 1;
	if (ft_strncmp(exec->cmd[0], "cd", 3) == 0)
		ret = 1;
	if (ft_strcmp(exec->cmd[0], "pwd") == 0)
		ret = 1;
	if (ft_strncmp(exec->cmd[0] , "export", 7) == 0)
        ret = 1;
	if (ft_strncmp (exec->cmd[0] , "env", 4) == 0)
		ret = 1;
    if (ft_strncmp (exec->cmd[0] , "unset", 6) == 0)
        ret = 1;
    if (ft_strncmp (exec->cmd[0] , "exit" , 5) == 0)
		ret = 1;
    return ret;
}
