#include "minishell.h"

char *duplicate_pwd(t_env *env)
{
    char *secure_value;
    char *lekher;
    char *secure_pwd;
    
    secure_value = find_env_variable2(env, "PWD");
    secure_pwd = ft_strdup("#PWD=");
    gc_add(0, secure_pwd);
    lekher = ft_strjoin2(secure_pwd, secure_value);
    gc_add(0 , lekher);
    return (lekher);
}

char *stop_after_delim(char *s, char spec)
{
    int i = 0;
    while(s[i] && s[i] != spec)
    {
        i++;
    }
    char *data = malloc(i + 1);
    gc_add(0 ,data);
    i = 0;
    while(s[i] && s[i] != spec)
    {
        data[i] = s[i];
        i++;
    }
    data[i] = '\0';
    return data;
}

int process_export_arg(t_env *env, char *arg)
{
    char *equal = strchr(arg, '=');
    char *plus = strchr(arg, '+');

    if (!equal)
        return export_without_value(env, arg);
    else
        return export_with_value(env, arg, equal, plus);
}

t_env *find_env_variable (t_env *env, char *varname)
{
    while (env)
    {
        if (ft_strcmp(env->variable, varname) == 0)
        {
            return env;
        }
        env = env->next;
    }
    return NULL;
}

t_env *creat_env_var (char *varname, char *value)
{
    t_env *new_var = malloc(sizeof(t_env));
    gc_add(0 , new_var);
    new_var->variable = varname;
    new_var->value = value;
    new_var->next = NULL;
    return new_var;
}