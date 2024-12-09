#include "ft_printf.h"

void	ft_putstr(int fd, char *str, int *c)
{
	if (!str)
	{
		ft_putstr(fd, "(null)", c);
		return ;
	}
	while (*str)
	{
		ft_putchar(fd, *str, c);
		str++;
	}
}