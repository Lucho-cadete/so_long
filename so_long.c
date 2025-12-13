/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:26:26 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/13 17:47:58 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(int fd)
{
	int		counter;
	char 	*line;

	counter = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		counter++;
		free (line);
		line = get_next_line(fd);
	}
	// printf("%d\n", counter);
	return(counter);
}

char	**read_map(int fd, int line_count)
{
	char	**map;
	char	*line;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * line_count);
	if (!map)
		return(NULL);
	while (i < line_count)
	{
		line = get_next_line(fd);
		map[i] = line;
		i++;
	}
	return (map);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		line_count;
	char 	**map;
	int i;

// Validacion.
	if (argc != 2)
	{
		ft_putstr_fd ("Error: Lack of args!", 2);
		return (1);
	}
// Primera apertura del fd solo para contar las lineas y saber cuanto malloc.
	fd = open (argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error by opening!");
		return (1);
	}

	line_count = count_lines(fd);
	close (fd);
// Segunda apertura del fd para hacer malloc.
	fd = open (argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error by opening!");
		return (1);
	}
	i = 0;
	map = read_map(fd, line_count);
	close(fd);
	if (!is_rectangular(map, line_count))
	{
		ft_putstr_fd("Error: Map is not rectangular!\n", 2);
		while (i < line_count)
		{
			free (map[i]);
			i++;
		}
		free (map);
		return(1);
	}
	if (!is_closed(map, line_count))
	{
		ft_putstr_fd("Error: Map is not closed!\n", 2);
		while (i < line_count)
		{
			free (map[i]);
			i++;
		}
		free (map);
		return(1);
	}
	if (!check_map_elements(map, line_count))
	{
		ft_putstr_fd("Error: Invalid number of elemets!\n", 2);
		while (i < line_count)
		{
			free (map[i]);
			i++;
		}
		free (map);
		return(1);
	}
	printf("✅ All the elements are where they to be!!!\n");

	if (!validate_path(map, line_count))
    {
        ft_putstr_fd("Error\n", 2);
        // liberar map
        return (1);
    }
//Printf para testear
	i = 0;
	while(i < line_count)
	{
		printf("%s", map[i]);
		i++;
	}
//Liberar mallocs!
	start_game(map, line_count);
	i = 0;
	while (i < line_count)
	{
		free (map[i]);
		i++;
	}
	free (map);
	printf ("\n\nMISION COMPLETED!!!\n");
	return (0);
}
