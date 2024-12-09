#include "minishell.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '_')
		return (1);
	else
		return (0);
}
