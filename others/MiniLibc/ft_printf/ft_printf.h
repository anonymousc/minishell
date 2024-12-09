/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:28 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:29:33 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

int		ft_printf(int fd, char const	*str, ...);

void	ft_spf(int fd, char spf, va_list args, int *l);
void	ft_unsigned(int fd, unsigned int nb, int *c);
void	ft_putchex(int fd, unsigned int l, int *c);
void	ft_puthex(int fd, unsigned long l, int *c);
void	ft_putptr(int fd, unsigned long l, int *c);
void	ft_putstr(int fd, char *str, int *c);
void	ft_putchar(int fd, char ch, int *c);
void	ft_putnbr(int fd, long nb, int *c);

#endif