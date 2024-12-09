#include "minishell.h"

int is_space(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}

char *is_space_veta(char s)
{
	if(s == ' ')
		return (" ");
	if(s == '\t')
		return ("\t");
	if(s == '\n')
		return ("\n");
	if(s == '\f')
		return ("\f");
	if(s == '\r')
		return ("\r");
	return NULL;
}