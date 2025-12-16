/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:58:18 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/16 23:10:46 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(char **map, int line_count, int *x, int *y)
{
	int	i;
	int	j;

	j = 0;
	while (j < line_count)
	{
		i = 0;
		while (map[j][i] != '\n' && map[j][i] != '\0')
		{
			if (map[j][i] == 'P')
			{
				*x = i;
				*y = j;
			}
			i++;
		}
		j++;
	}
}

void	fill_line_with_ceros(char *line, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		line[i] = '0';
		i++;
	}
	line[width] = '\0';
}

char	**create_parallel_map(int line_count, int width)
{
	char	**map_visited;
	int		j;

	j = 0;
	map_visited = malloc(sizeof(char *) * line_count);
	if (!map_visited)
		return (NULL);
	while (j < line_count)
	{
		map_visited[j] = malloc(sizeof(char) * (width + 1));
		if (!map_visited[j])
		{
			while (j > 0)
			{
				j--;
				free(map_visited[j]);
			}
			free(map_visited);
			return (NULL);
		}
		fill_line_with_ceros(map_visited[j], width);
		j++;
	}
	return (map_visited);
}

void	free_visited_map(char **visited, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	validate_path(char **map, int line_count)
{
	t_maps			maps;
	t_position		player;
	t_flood_data	data;
	int				total_c;

	if (!setup_flood_fill(map, line_count, &maps, &player))
		return (0);
	total_c = count_c(map, line_count);
	data = (t_flood_data){0, 0};
	flood_fill(&maps, player.x, player.y, &data);
	free_visited_map(maps.visited, line_count);
	if (data.count_c != total_c)
	{
		printf ("Some collectibles are not reachable.\n");
		return (0);
	}
	if (data.found_e == 0)
	{
		printf ("Exit not reachable!\n!!!");
		return (0);
	}
	return (1);
}
