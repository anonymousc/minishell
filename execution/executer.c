#include "minishell.h"

void execute_bins(t_execution **exec, char **env, t_env **env1 )
{
    t_execution *curr = *exec;
    char *fullcmd;
    pid_t *pids;
    int cmd_count;
    int i = 0;
    int prev_pipe[2] = {0, 1};
    int curr_pipe[2];
    int flag = 0;
    // int tmp = 0;
    cmd_count = ft_cmd_count(curr);
    pids = malloc(sizeof(pid_t) * cmd_count);
    gc_add(0 , pids, NULL);
    while (curr && i < cmd_count)
    {
        if (i < cmd_count - 1)
            pipe(curr_pipe);
        if (cmd_count == 1 && check_builtins(curr))
            return (exit_status = execute_builtins(curr, env1, env), env = env_to_arr2(*env1) , gc_add(0 , env , NULL), (void)0);
        pids[i] = fork();
        signal(SIGQUIT , sig_handler1);
        signal(SIGINT, sigfork);
        if (pids[i] == 0)
        {
            signal(SIGINT, sig_heredoc);
            signal(SIGQUIT , SIG_DFL);
            if (redirect_io(&curr, &flag) == -1)
                return (exit_minishell(1) , (void)0);
            if (i > 0)
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                ft_close(&prev_pipe[0] , &prev_pipe[1]);
            }
            if (i < cmd_count - 1)
            {
                if (flag == 0)
                    dup2(curr_pipe[1], STDOUT_FILENO);
                ft_close(&curr_pipe[0] , &curr_pipe[1]);
            }
            if (curr->cmd[0] == NULL)
                return (exit_minishell(1) ,(void)0);
            env = env_to_arr2(*env1);
            gc_add(0 , env, NULL);
            if (cmd_count > 1 && check_builtins(curr))
            {
                if (flag == 1)
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
            else
            {
                fullcmd = find_path(curr->cmd[0], env);
                if((curr->cmd[0][0]) != '\0')
                {
                    struct stat data;
                    if (stat(fullcmd, &data) == 0 && S_ISDIR(data.st_mode))
                        return (printf("%s is directory\n", fullcmd) ,exit_minishell(126) , (void)0);
                    if (!fullcmd)
                    {
                        fprintf(stderr, "Command not found: %s\n", curr->cmd[0]);
                        exit_minishell(127);
                    }
                }
                if (execve(fullcmd, curr->cmd, env) == -1)
                    return (perror("minishell")  ,exit_minishell(126) ,(void)0);
            }
        }
        else
        {
            if (i > 0)
                ft_close(&prev_pipe[0] , &prev_pipe[1]);
            if (i < cmd_count - 1)
            {
                prev_pipe[0] = curr_pipe[0];
                prev_pipe[1] = curr_pipe[1];
            }
        }
        curr = curr->next;
        i++;
    }
    i = -1;
    int tmp1 = exit_status;
    while (++i < cmd_count)
       waitpid(pids[i], &exit_status, 0);
    if(WIFEXITED(exit_status))
        exit_status = (char)WEXITSTATUS(exit_status);
    // tmp = exit_status;
    if(tmp1 == 130)
        exit_status = tmp1;
}