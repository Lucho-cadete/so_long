/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:58:18 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/15 22:19:16 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	setup_flood_fill(char **map, int line_count, t_maps *maps,
					t_position *player)
{
	int	width;

	width = ft_strlen(map[0]);
	if (width > 0 && map[0][width - 1] == '\n')
		width--;
	maps->visited = create_parallel_map(line_count, width);
	if (!maps->visited)
		return (0);
	find_player(map, line_count, &player->x, &player->y);
	maps->original = map;
	maps->width = width;
	maps->height = line_count;
	return (1);
}

void	flood_fill(t_maps *maps, int x, int y, t_flood_data *data)
{
	if (x < 0 || y < 0 || x >= maps->width || y >= maps->height)
		return ;
	if (maps->original[y][x] == '1')
		return ;
	if (maps->visited[y][x] == '1')
		return ;
	maps->visited[y][x] = '1';
	if (maps->original[y][x] == 'C')
		data->count_c++;
	if (maps->original[y][x] == 'E')
		data->found_e = 1;
	flood_fill(maps, x, y - 1, data);
	flood_fill(maps, x, y + 1, data);
	flood_fill(maps, x - 1, y, data);
	flood_fill(maps, x + 1, y, data);
}
