#include "minishell.h"

void sig_handler(int test)
{
	(void)test;
	printf("\n");
	rl_on_new_line ();
	rl_replace_line ("", 0);
	rl_redisplay();
	exit_status = 130;
	return ;
}

void sig_handler1(int test)
{
	(void)test;
	exit_status = 131;
	printf("\n");
	return ;
}

void sig_heredoc(int test)
{
    (void)test;
    printf("\n");
    exit_minishell(130);
}

void sigfork(int data)
{
    (void)data;
    exit_status = 130;
    printf("\n");
}