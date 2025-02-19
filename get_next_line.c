/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrgonza <isrgonza@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:53:57 by isrgonza          #+#    #+#             */
/*   Updated: 2025/02/04 10:56:09 by isrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_read_n_stock(int fd, char *stash)
{
	int		char_read;
	char	*buf;

	buf = allocate_buffer();
	if (!buf)
		return (NULL);
	char_read = 1;
	while (char_read > 0)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1)
			return (handle_read_error(buf, stash));
		buf[char_read] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (handle_read_error(buf, NULL));
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(buf);
	return (stash);
}

static char	*search_endline(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*move_pos_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = malloc(ft_strlen(stash) - i + 1);
	if (!str)
	{
		free(stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i])
		str[j++] = stash[i++];
	str[j] = '\0';
	free(stash);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_n_stock(fd, stash);
	if (!stash)
		return (NULL);
	line = search_endline(stash);
	stash = move_pos_stash(stash);
	return (line);
}
