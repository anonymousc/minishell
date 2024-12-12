/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:24:59 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:26:19 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_spf(int fd, char spf, va_list args, int *l)
{
	if (spf == 's')
		ft_putstr(fd, va_arg(args, char *), l);
	else if (spf == 'c')
		ft_putchar(fd, va_arg(args, int), l);
	else if (spf == 'd')
		ft_putnbr(fd, va_arg(args, int), l);
	else if (spf == 'i')
		ft_putnbr(fd, va_arg(args, int), l);
	else if (spf == 'u')
		ft_unsigned(fd, va_arg(args, unsigned int), l);
	else if (spf == 'x')
		ft_puthex(fd, va_arg(args, unsigned int), l);
	else if (spf == 'X')
		ft_putchex(fd, va_arg(args, unsigned int), l);
	else if (spf == 'p')
		ft_putptr(fd, va_arg(args, unsigned long), l);
	else
		ft_putchar(fd, spf, l);
}
