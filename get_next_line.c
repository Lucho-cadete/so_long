/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:21:43 by luimarti          #+#    #+#             */
/*   Updated: 2025/11/25 09:37:59 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*extract_line(char *rest)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = rest [j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_rest(char *rest)
{
	char	*leftover;
	size_t	i;

	i = 0;
	if (!rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i] || !rest[i + 1])
	{
		free (rest);
		return (NULL);
	}
	i++;
	leftover = ft_strdup(rest + i);
	free (rest);
	return (leftover);
}

char	*add_rest(char *rest, char *buffer)
{
	char	*new_rest;
	int		len_rest;
	int		len_buffer;
	int		any;

	len_rest = 0;
	len_buffer = 0;
	if (rest)
		len_rest = ft_strlen_and_find_newline(rest, &any);
	if (buffer)
		len_buffer = ft_strlen_and_find_newline(buffer, &any);
	new_rest = malloc(len_rest + len_buffer + 1);
	if (!new_rest)
		return (free(rest), NULL);
	new_rest[0] = '\0';
	if (rest)
		ft_strcpy(new_rest, rest);
	if (buffer)
		ft_strcat(new_rest, buffer);
	free (rest);
	return (new_rest);
}

int	read_and_update_rest(int fd, char **rest)
{
	char	*buffer;
	int		read_bytes;
	int		find_newline;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	read_bytes = 0;
	while (!*rest || !ft_strlen_and_find_newline(*rest, &find_newline)
		|| !find_newline)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		*rest = add_rest(*rest, buffer);
		if (*rest == NULL)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	return (read_bytes);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = read_and_update_rest(fd, &rest);
	if (read_bytes < 0 || (read_bytes == 0 && (!rest || *rest == '\0')))
		return (free(rest), rest = NULL, NULL);
	line = extract_line(rest);
	if (line == NULL)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	rest = extract_rest(rest);
	return (line);
}
