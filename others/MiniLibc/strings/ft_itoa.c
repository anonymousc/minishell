#include "minishell.h"

static long	ft_count(long n)
{
	long	ft_counter;

	ft_counter = 0;
	if (n <= 0)
		ft_counter += 1;
	while (n != 0)
	{
		n /= 10;
		ft_counter++;
	}
	return (ft_counter);
}

static char	*is_negative(char *str, long n, long ft_counter)
{
	long	i;

	i = ft_counter - 1;
	n *= -1;
	while (i > 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	str[i] = '-';
	return (str);
}

static char	*is_positive(char *str, long n, long ft_counter)
{
	long	i;

	i = ft_counter - 1;
	while (i >= 0)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	ft_counter;
	long	nb;

	nb = n;
	ft_counter = ft_count(nb);
	str = malloc (sizeof(char) * (ft_counter + 1));
	if (str == NULL)
		return (NULL);
	str[ft_counter] = '\0';
	if (nb == 0)
		*str = 0 + '0';
	if (nb < 0)
		str = is_negative(str, nb, ft_counter);
	if (nb > 0)
		str = is_positive(str, nb, ft_counter);
	return (str);
}