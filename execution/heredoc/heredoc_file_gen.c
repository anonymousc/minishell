/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_gen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:38:57 by aait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:52:10 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*namegen(void)
{
	int		fd;
	int		i;
	char	*file;
	char	*buf;
	int		j;

	fd = open("/dev/random", O_RDONLY);
	i = 0;
	file = malloc(11);
	gc_add(0, file);
	buf = malloc(1);
	gc_add(0, buf);
	j = 0;
	while (i < 10)
	{
		read(fd, buf, 1);
		if (ft_isascii(*buf))
			file[j++] = *buf;
		i++;
	}
	file[j] = '\0';
	close(fd);
	return (file);
}

char	*randgen(char *s)
{
	char	*pathname;

	pathname = "/tmp/";
	s = ft_strjoin(pathname, namegen());
	return (s);
}

int	file_to_write_on(char **filename)
{
	char	*path;
	int		fd;

	path = randgen(*filename);
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	*filename = path;
	gc_add(0, path);
	return (fd);
}
