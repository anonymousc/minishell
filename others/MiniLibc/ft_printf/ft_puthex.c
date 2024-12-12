/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:24:32 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:26:14 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(int fd, unsigned long l, int *c)
{
	if (l >= 16)
		ft_puthex(fd, l / 16, c);
	ft_putchar(fd, "0123456789abcdef"[l % 16], c);
}
