/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcherx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:55 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:26:12 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchex(int fd, unsigned int l, int *c)
{
	if (l >= 16)
		ft_putchex(fd, l / 16, c);
	ft_putchar(fd, "0123456789ABCDEF"[l % 16], c);
}
