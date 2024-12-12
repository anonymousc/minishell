/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:37:45 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:37:46 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *nptr)
{
	int					i;
	int					s;
	unsigned long long	r;

	i = 0;
	s = 1;
	r = 0;
	while (nptr && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr && nptr[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (nptr && nptr[i] == '+')
		i++;
	while (nptr && nptr[i] >= '0' && nptr[i] <= '9')
		r = r * 10 + nptr[i++] - '0';
	return ((int)(r * s));
}
