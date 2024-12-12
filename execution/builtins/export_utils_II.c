#include "minishell.h"

void swap(char **s1, char **s2)
{
    char *tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
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
