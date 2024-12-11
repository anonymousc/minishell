#include "minishell.h"

void swap(char **s1, char **s2)
{
    char *tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

char **env_to_arr2(t_env *env)
{
    int size = env_size(env);
    char **envir = malloc(sizeof(char *) * (size + 1));
    gc_add(0 , envir);
    if (!envir)
        return NULL;

    int i = 0;
    while (env)
    {
        int var_len = ft_strlen(env->variable);
        int val_len = ft_strlen(env->value);
        int len = var_len + val_len + 1 + 3 * (val_len != 0);

        envir[i] = malloc(len);
        gc_add(0 , envir[i]);
        int j = 0;
        if (!envir[i])
        {
            while (j < i)
               j++;
            return NULL;
        }
        j = 0;
        int k = 0;
        while (k < var_len)
            envir[i][j++] = env->variable[k++];
        if(val_len)
        {
            envir[i][j++] = '=';
            k = 0;
            while (k < val_len)
                envir[i][j++] = env->value[k++];
        }
        envir[i][j] = '\0';
        env = env->next;
        i++;
    }
    envir[i] = NULL;
    return envir;
}


char **sort_strings(char **str, int len) 
{
    int i = 0;
    int j;
    while (i < len - 1) 
    { 
        j = i + 1;
        while (j < len) 
        {
            if (ft_strcmp(str[i], str[j]) > 0) 
            {
                swap(&str[i], &str[j]);
            }
            j++;
        }
        i++;
    }
    return str;
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

int is_valid_identifier (int fd, char *arg)
{
    int  i = 1;
    fd = 2;
    if (!ft_isalpha(arg[0]) && arg[0] != '_')
    {
        ft_printf (fd ,"%s not a valid identifier\n", arg);
        return -1;
    }
    while (arg[i] && (arg[i] != '+' && arg[i] != '='))
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
        {
            ft_printf (fd, "%s not a valid identifier\n", arg);
            return -1;
        }
        i++;
    }
    return 0;
}

int update_existing_var(t_env *existing, char *value, int is_append)
{
    char *new_value;

    if (is_append)
    {
        new_value = ft_strjoin(existing->value, value);
        gc_add(0 , new_value);
        if (!new_value)
            return 0; 
        existing->value = new_value;
    }
    else
    {
        new_value = ft_strdup(value);
        gc_add(0 , new_value);
        if (!new_value)
            return 0;
        existing->value = new_value;
    }
    return 1;
}


int handle_existing_var(t_env *env, char *var_name, char *value, int is_append)
{
    t_env *existing = find_env_variable(env, var_name);
    t_env *new_var;

    if (existing)
    {
        return update_existing_var(existing, value, is_append);
    }
    else
    {
        if (is_append)
            new_var = creat_env_var(var_name, value);
        else
            new_var = creat_env_var(var_name, value); 

        if (!new_var)
            return 0;

        add_back(&(env), new_var);
    }
    return 1;
}

int export_with_value(t_env *env, char *arg, char *equal, char *plus)
{
    int is_append;
    int name_len;
    char *var_name;
    char *value;

    is_append = (plus && plus + 1 == equal);
    if (is_append)
        name_len = plus - arg;
    else
        name_len = equal - arg;
    var_name = malloc(name_len + 1);
    gc_add(0 , var_name);
    ft_strncpy(var_name, arg, name_len);
    var_name[name_len] = '\0';
    value = equal + 1;
    if (!handle_existing_var(env, var_name, value, is_append))
        return 0;
    return 1;
}

int export_without_value(t_env *env, char *arg)
{
    t_env *existing = find_env_variable(env, arg);
    t_env *new_var;

    if (!existing)
    {
        new_var = creat_env_var(arg, "");
        if (!new_var)
            return 0;
        add_back(&(env), new_var);
    }
    return 1;
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
char *stop_after_delim(char *s, char spec)
{
    int i = 0;
    while(s[i] != spec)
    {
        i++;
    }
    char *data = malloc(i + 1);
    gc_add(0 ,data);
    i = 0;
    while(s[i] != spec)
    {
        data[i] = s[i];
        i++;
    }
    data[i] = '\0';
    return data;
}
static int handle_single_args(char **env_array , int *fd_append, int *fd_out)
{
    int i;

    i = 0;
    while (env_array[i])
    {
        if (env_array[i][0] == '#') 
        {
            i++;
            continue;
        }
        if(*fd_append == 1)
            ft_printf(*fd_out, "declare -x %s=\"%s\"\n", stop_after_delim(env_array[i], '=')
            , ft_strchr(env_array[i] , '=') + 1);
        else
            ft_printf(*fd_append, "declare -x %s=\"%s\"\n", stop_after_delim(env_array[i], '=')
            , ft_strchr(env_array[i] , '=') + 1);
        i++;
    }
    return 0;

}

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

int my_export(t_execution *exec , t_env **env, int fd, int fda)
{
    int i;
    char *lekher;
    char **env_array;
    char *arg;

    env_array = sort_strings(env_to_arr2(*env), env_size(*env));
    lekher = duplicate_pwd(*env);
    if(!exec)
        return (process_export_arg(*env , lekher) ,0);
    if (!exec->cmd[1])
        return (handle_single_args(env_array , &fda , &fd));
    i = 1;
    while (exec->cmd[i])
    {
        arg = exec->cmd[i];
        if (is_valid_identifier(fd, arg) < 0)
            return 1;
        if (!process_export_arg(*env, arg))
            return 1;
        i++;
    }
    return 0;
}
