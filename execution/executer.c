#include "minishell.h"

void builtins_pipe(t_execution *curr ,char **env ,t_env **env1 ,int *flag)
{
    if (*flag == 1)
    {
        if (curr->fds[0] != 1)
        {
            dup2 (STDOUT_FILENO, curr->fds[0]);
            close(STDOUT_FILENO);
        }
        if (curr->fds[2] != 1)
        {
            dup2 (STDOUT_FILENO, curr->fds[2]);
            close(STDOUT_FILENO);
        }
    }
    exit_status = execute_builtins(curr, env1, env);
    return (exit_minishell(0), (void)0);
}
void ft_execve(t_execution *curr ,char **env)
{
    char *fullcmd;

    if(check_builtins(curr))
        exit_minishell(0);
    if(curr->cmd)
    { 
        fullcmd = find_path(curr->cmd[0], env);
        struct stat data;
        if (stat(fullcmd, &data) == 0 && S_ISDIR(data.st_mode))
            return (ft_printf(2, "%s is directory\n", fullcmd) ,exit_minishell(126) , (void)0);
        if (!fullcmd || !*fullcmd)
        {
            ft_printf(2, "Command not found: %s\n", curr->cmd[0]);
            exit_minishell(127);
        }
        if (execve(fullcmd, curr->cmd, env) == -1)
            return (perror("minishell")  ,exit_minishell(126) ,(void)0);
    }
}

void parent(int *i ,int *cmd_count , int *prev_pipe, int *curr_pipe)
{
    if (*i > 0)
        ft_close(&prev_pipe[0] , &prev_pipe[1]);
    if (*i < (*cmd_count) - 1)
    {
        prev_pipe[0] = curr_pipe[0];
        prev_pipe[1] = curr_pipe[1];
    }
}
void wait_for_children(int *pids, int *cmd_count)
{
    int tmp1;
    int i = -1;

    tmp1 = exit_status;
    while (++i < *cmd_count)
       waitpid(pids[i], &exit_status, 0);
    if(WIFEXITED(exit_status))
        exit_status = (char)WEXITSTATUS(exit_status);
    if(tmp1 == 130)
        exit_status = tmp1;
}
int prepare_child_process(int *i, int *cmd_count, int *curr_pipe)
{
    signal(SIGINT, sig_heredoc);
    signal(SIGQUIT, SIG_DFL);
    if (*i < *cmd_count - 1)
        pipe(curr_pipe);
    return 0;
}

int setup_input_redirection(int *i, int *prev_pipe)
{
    if (*i > 0)
    {
        if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
            return -1;
        ft_close(&prev_pipe[0], &prev_pipe[1]);
    }
    return 0;
}

int setup_output_redirection(int *i, int *cmd_count, int *curr_pipe, int *flag)
{
    if (*i < *cmd_count - 1)
    {
        if (*flag == 0 && dup2(curr_pipe[1], STDOUT_FILENO) == -1)
            return -1;
        ft_close(&curr_pipe[0], &curr_pipe[1]);
    }
    return 0;
}

void execute_child_command(t_execution *curr, char **env, t_env **env1, int **array, t_syntax *data)
{
    int *prev_pipe;
    int *curr_pipe;

    prev_pipe = array[1];
    curr_pipe = array[2];
    if (curr->cmd[0][0] == '\0')
        exit_minishell(0);
    if (redirect_io(&curr, &data->flag) == -1)
        exit_minishell(1);
    if (setup_input_redirection(&data->iter, prev_pipe) == -1)
        exit_minishell(1);
    if (setup_output_redirection(&data->iter, &data->cmd_count, curr_pipe, &data->flag) == -1)
        exit_minishell(1);
    env = env_to_arr2(*env1);
    if (data->cmd_count > 1 && check_builtins(curr))
        builtins_pipe(curr, env, env1, &data->flag);
    else   
        ft_execve(curr, env);
}
void exec_single_builtin(t_execution *curr , char **env , t_env **env1 , int *cmd_count)
{
    if (*cmd_count == 1 && check_builtins(curr))
    {
        exit_status = execute_builtins(curr, env1, env);
        env = env_to_arr2(*env1);
    }
}

int **init_var_pipes(int **array, t_syntax *data)
{
    array = malloc(sizeof(int *) * 3);
    gc_add(0 ,array , NULL);
    array[0] = malloc(sizeof(pid_t) * data->cmd_count);
    gc_add(0 , array[0], NULL);
    array[1] = malloc(sizeof(int)  * 2);
    gc_add(0 , array[1], NULL);
    array[1][0] = 0;
    array[1][1] = 1;
    array[2] = malloc(sizeof(int)  * 2);
    gc_add(0 , array[2], NULL);
    return array;
}
void execute_bins(t_execution **exec, char **env, t_env **env1)
{
    t_execution *curr;
    t_syntax data;
    int **array;

    array = NULL;
    curr = *exec;
    data.iter = 0;
    data.flag = 0;
    data.cmd_count = ft_cmd_count(curr);
    array = init_var_pipes(array , &data);
    while (curr && data.iter < data.cmd_count)
    {
        exec_single_builtin(curr , env , env1 , &data.cmd_count);
        prepare_child_process(&data.iter , &data.cmd_count, array[2]);
        array[0][data.iter] = fork();
        if (array[0][data.iter] == 0)
            execute_child_command(curr , env , env1 , array ,&data);
        else
            parent(&data.iter , &data.cmd_count , array[1] , array[2]);
        curr = curr->next;
        data.iter++;
    }
    wait_for_children(array[0] , &data.cmd_count);
}
