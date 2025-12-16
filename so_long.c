/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:26:26 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/16 23:42:56 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map(int fd, int line_count)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * line_count);
	if (!map)
		return (NULL);
	while (i < line_count)
	{
		line = get_next_line(fd);
		map[i] = line;
		i++;
	}
	return (map);
}

int	validate_map_structure(char **map, int line_count)
{
	if (line_count == 0 || !map || !map[0])
	{
		ft_putstr_fd("Error: Empty map\n", 2);
		free(map);
		exit(1);
	}
	if (!is_rectangular(map, line_count))
	{
		ft_putstr_fd("Error: Map is not rectangular!\n", 2);
		free_map(map, line_count);
		exit(1);
	}
	if (!is_closed(map, line_count))
	{
		ft_putstr_fd("Error: Map is not closed!\n", 2);
		free_map(map, line_count);
		exit(1);
	}
	return (1);
}

int	validate_map_content(char **map, int line_count)
{
	if (!check_map_elements(map, line_count))
	{
		ft_putstr_fd("Error: Invalid number of elemets!\n", 2);
		free_map(map, line_count);
		exit(1);
	}
	if (!validate_path(map, line_count))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (1);
}

int	safe_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error by opening!");
		exit(1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		line_count;
	char	**map;

	if (argc != 2)
	{
		ft_putstr_fd ("Error: Lack of args!", 2);
		return (1);
	}
	fd = open (argv[1], O_RDONLY);
	fd = safe_open(argv[1]);
	line_count = count_lines(fd);
	close (fd);
	fd = open (argv[1], O_RDONLY);
	fd = safe_open(argv[1]);
	map = read_map(fd, line_count);
	close(fd);
	validate_map_structure(map, line_count);
	validate_map_content(map, line_count);
	start_game(map, line_count);
	return (0);
}
