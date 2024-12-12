#include "minishell.h"

int my_cd(t_execution *exec , t_env *env)
{
    char *old_pwd = malloc(sizeof(char) * PATH_MAX);
    gc_add(0 , old_pwd);
    if(handle_single_argument(env , exec))
            return (1);
    if (getcwd(old_pwd, PATH_MAX) == NULL)
        return (perror("getcwd") ,1);
    if (chdir(exec->cmd[1]) != 0)
        return (perror("cd") ,1);
    if (find_variable(env, "PWD"))
        update_oldpwd(env, find_env_variable2(env, "PWD"));
    else
        update_oldpwd(env, old_pwd);
    update_pwd(env);
    return 0;
}
