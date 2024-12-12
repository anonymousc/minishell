/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:24:55 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:26:17 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
