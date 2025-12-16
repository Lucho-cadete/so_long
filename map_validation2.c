/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:13:29 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/16 23:43:22 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_horizontal_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_vertical_walls(char **map, int line_count, size_t width)
{
	int	j;

	j = 1;
	while (j < line_count - 1)
	{
		if (map[j][0] != '1' || map[j][width - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	is_closed(char **map, int line_count)
{
	size_t	width;

	if (!check_horizontal_wall(map[0]))
		return (0);
	if (!check_horizontal_wall(map[line_count - 1]))
		return (0);
	width = ft_strlen(map[0]);
	if (width > 0 && map[0][width - 1] == '\n')
		width--;
	if (!check_vertical_walls(map, line_count, width))
		return (0);
	return (1);
}

int	count_lines(int fd)
{
	int		counter;
	char	*line;

	counter = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		counter++;
		free (line);
		line = get_next_line(fd);
	}
	return (counter);
}
