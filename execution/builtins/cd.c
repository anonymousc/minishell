#include "minishell.h"

static t_env *find_variable(t_env *env, char *variable_name)
{
    while (env)
    {
        if (ft_strcmp(env->variable, variable_name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

static void update_env_value(t_env *env, char *variable_name, char *new_value)
{
    t_env *var = find_variable(env, variable_name);
    if (var)
           var->value = ft_strdup(new_value);
    else
        return ;
    gc_add(0 , var->value);
}

static void update_oldpwd(t_env *env, char *old_pwd)
{
        update_env_value(env, "OLDPWD", old_pwd);
}

static void update_pwd(t_env *env)
{
    char cwd;
    
    cwd = malloc(sizeof(char) * PATH_MAX);
    gc_add(0 ,cwd);
    if (getcwd(cwd, PATH_MAX) != NULL)
        update_env_value(env, "PWD", cwd);
    else
        perror("getcwd error");
}
static int handle_single_argument(t_env *env ,  t_execution *exec)
{
    if (!exec->cmd[1])
    {
        if (chdir(find_env_variable2(env, "HOME")) != 0)
           perror("cd : HOME not set");
        update_oldpwd (env, find_env_variable2(env, "#PWD"));
        update_pwd(env);
        return 1;
    }
    chdir(find_env_variable2(env, "#PWD"));
    return 0;
}
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
    update_oldpwd(env, old_pwd);
    update_pwd(env);
    return 0;
}
