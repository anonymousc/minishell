#include "minishell.h"

t_env *get_last(t_env *envir)
{
    if (!envir)
        return NULL;
    while(envir->next)
        envir = envir->next;
    return envir;
}

void add_back(t_env **envir, t_env *var)
{
    t_env *last = get_last(*envir);
    if (!*envir)
    {
        *envir = var;
    }
    else
    {
        last->next = var;
    }
    var->next = NULL;
}

t_env *lstnew_env(char *variable , char *value)
{
    t_env *env;
    env = malloc(sizeof(t_env));
    gc_add(0 , env);
    env->variable = variable;
    gc_add(0 , env->variable);
    env->value = value;
    gc_add(0 , env->value);
    env->next = NULL;
    return (env);
}

t_env *make_env(char **env_original)
{
    int i;
    t_env *envir;
    char *delimiter;

    envir = NULL;
    i = 0;
    while (env_original && env_original[i])
    {
        delimiter = ft_strchr(env_original[i], '=');
        if (!delimiter)
            return (NULL);
        add_back(&envir,\
        lstnew_env(ft_strndup(env_original[i], delimiter - env_original[i]) \
        , ft_strdup(delimiter + 1)));
        i++;
    }
    return envir;
}

int env_size(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}