#include "minishell.h"


int ft_cmd_count(t_execution * curr)
{
    t_execution *temp;
    int         cmd_counter;

    temp = curr;
    cmd_counter = 0;
    while (temp)
    {
        cmd_counter++;
        temp = temp->next;
    }
    return (cmd_counter);
}

void ft_close(int *fd1 , int *fd2)
{
    close(*fd1);
    close(*fd2);
}

char *find_path(char *cmd, char **env)
{
    char *full_path;
    char *full_command;
    char **paths = NULL;
    char *path_var = NULL;
    if(!cmd)
        return NULL;
    if ((ft_strchr(cmd , '/') || ft_strchr(cmd , '.')))
    {
        if (!access(cmd , F_OK ))
            return cmd;
        else
            return NULL;
    }
    int j = 0;
    while (env && env[j])
    {
        if (ft_strncmp(env[j], "PATH=", 5) == 0)
        {
            path_var = env[j] + 5;
            break;
        }
        j++;
    }
    if (!path_var)
        return NULL;
    if(ft_strchr(path_var , ':'))
    {
        paths = ft_split(path_var, ':');
        gc_add_double(0 , (void **)paths, NULL);
    }
    else
    {
        paths = (char **)malloc(2 * sizeof(char *));
        gc_add(0 , paths , NULL);
        paths[0] = remove_quotes(path_var);
        paths[1] = NULL;

    }
    int i = 0;
    while (paths && paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        gc_add(0 , full_path, NULL);
        full_command = ft_strjoin(full_path, cmd);
        gc_add(0 , full_command, NULL);
        if (access(full_command, F_OK | X_OK) == 0)
            return (full_command);
        i++;    
	}
    return NULL;
}