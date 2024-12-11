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
    gc_add(0 , var->value, NULL);
}

static void update_oldpwd(t_env *env, char *old_pwd)
{
        update_env_value(env, "OLDPWD", old_pwd);
}

static void update_pwd(t_env *env)
{
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_env_value(env, "PWD", cwd);
    else
        perror("getcwd error");
}

int my_cd(t_execution *exec , t_env *env)
{
    char old_pwd[4096];

    if (!exec->cmd[1])
    {
        if (chdir(find_env_variable2(env, "HOME")) != 0)
           perror("cd : HOME not set");
        update_oldpwd (env, find_env_variable2(env, "#PWD"));
        update_pwd(env);
        return 1;
    }
    if(!(*exec->cmd[1]))
    {
        chdir(find_env_variable2(env, "#PWD"));
        return 0;
    }
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd");
        return 1;
    }
    if (chdir(exec->cmd[1]) != 0)
    {
        perror("cd");
        return 1;
    }
    update_oldpwd(env, old_pwd);
    update_pwd(env);
    return 0;
}
