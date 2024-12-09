/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:29:53 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, char const *str, ...)
{
	int		l;
	va_list	args;

	l = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			ft_spf(fd, *(str + 1), args, &l);
			str++;
		}
		else if (*str != '%')
			ft_putchar(fd, *str, &l);
		str++;
	}
	va_end(args);
	return (l);
}