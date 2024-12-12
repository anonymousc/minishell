/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:38:24 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:38:25 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	isleft;

	if (!s)
		return (0);
	if (start >= ft_strlen(s) || !len)
	{
		ss = (char *)malloc((1) * sizeof(char));
		if (ss == NULL)
			return (NULL);
		ss[0] = '\0';
		return (ss);
	}
	isleft = ft_strlen(s + start);
	if (len > isleft)
		len = isleft;
	ss = (char *)malloc((len + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	ss = ft_memcpy(ss, s + start, len);
	ss[len] = '\0';
	return (ss);
}
