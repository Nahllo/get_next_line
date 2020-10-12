/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:16:49 by jchauvet          #+#    #+#             */
/*   Updated: 2019/12/02 10:59:33 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				has_n(char *str, int mode)
{
	int i;

	i = 0;
	if (mode == 0)
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			return (i);
		return (-1);
	}
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char			*join_and_free(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	char	*tmp;

	tmp = s1;
	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (has_n(s1, 1) + has_n(s2, 1) + 1));
	if (res == 0)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(tmp);
	return (res);
}

void			set_zero_and_leftovers(char *line, char *leftovers)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		line[i] = 0;
		i++;
		while (line[j + i])
		{
			leftovers[j] = line[i + j];
			j++;
		}
	}
	leftovers[j] = 0;
}

int				init_and_error(int fd, char **line, char *buffer)
{
	if (line == NULL || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = 0;
	buffer[0] = 0;
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char		leftovers[BUFFER_SIZE + 1];
	char			buffer[BUFFER_SIZE + 1];
	int				i;
	int				k;

	if (init_and_error(fd, line, buffer) == -1)
		return (-1);
	*line = join_and_free(*line, leftovers);
	while ((has_n(*line, 0) == -1) && (i = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[i] = 0;
		*line = join_and_free(*line, buffer);
	}
	k = has_n(*line, 0);
	set_zero_and_leftovers(*line, leftovers);
	return ((i == -1 || fd == -1) ? -1 : k != -1);
}
