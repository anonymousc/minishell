/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:24:07 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:24:08 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_printf(int fd, char const *str, ...);

void	ft_spf(int fd, char spf, va_list args, int *l);
void	ft_unsigned(int fd, unsigned int nb, int *c);
void	ft_putchex(int fd, unsigned int l, int *c);
void	ft_puthex(int fd, unsigned long l, int *c);
void	ft_putptr(int fd, unsigned long l, int *c);
void	ft_putstr(int fd, char *str, int *c);
void	ft_putchar(int fd, char ch, int *c);
void	ft_putnbr(int fd, long nb, int *c);

#endif