/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:27:07 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:33:42 by kali             ###   ########.fr       */
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