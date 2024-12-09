#include "minishell.h"

static int handle_output_redirection(t_execution **exec, int *flag)
{
    if ((*exec)->fds[0] != 1)
    {
        if ((*exec)->fds[4] == -1)
            return (printf("permission denied\n"), -1);
        *flag = 1;
        dup2((*exec)->fds[0], STDOUT_FILENO);
        if ((*exec)->fds[0] != STDOUT_FILENO)
            close((*exec)->fds[0]);
    }
    return 0;
}

static int handle_append_redirection(t_execution **exec , int *flag)
{
    if ((*exec)->fds[2] != 1)
    {
        if ((*exec)->fds[4] == 1)
            return (printf("permission denied\n"), -1);
        *flag = 1;
        dup2((*exec)->fds[2], STDOUT_FILENO);
        close((*exec)->fds[2]);
    }
    return 0;
}

static int handle_input_redirection(t_execution **exec)
{
    if ((*exec)->fds[1] != 0)
    {
        if ((*exec)->fds[1] == -1 || (*exec)->fds[4] == 1)
        {
            printf("no such a file or directory\n");
            return -1;
        }
        dup2((*exec)->fds[1], STDIN_FILENO);
        close((*exec)->fds[1]);
    }
    return 0;
}

static int handle_heredoc_redirection(t_execution **exec)
{
    if ((*exec)->fds[3] != 0)
    {
        dup2((*exec)->fds[3], STDIN_FILENO);
        close((*exec)->fds[3]);
    }
    return 0;
}
int redirect_io(t_execution **exec, int *flag)
{
    if ((*exec)->fds[5] == 1)
        return (printf("this is a directory\n"), -1);
    if ((*exec)->fds[4] == 3)
        return (printf("ambigous redirection\n"), -1);
    if ((*exec)->fds[4] == 2)
        return (printf("no such a file or directory\n"), -1);
    if (handle_output_redirection(exec, flag) == -1)
        return -1;
    if (handle_append_redirection(exec , flag) == -1)
        return -1;
    if (handle_input_redirection(exec) == -1)
        return -1;
    handle_heredoc_redirection(exec);

    return 0;
}