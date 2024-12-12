#include "minishell.h"

int my_env(int fd, int fda, t_env **env)
{
    t_env *curr = *env;
    while (curr)
    {
        if (curr->value[0] == '\0' || curr->variable[0] == '#') 
        {
            curr = curr->next;
            continue;
        }
        if(fda == 1)
            ft_printf(fd, "%s=%s\n", curr->variable, curr->value);
        else
            ft_printf(fda, "%s=%s\n", curr->variable, curr->value);
        curr = curr->next;
    }
    return 0;
}
