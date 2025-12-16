/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:46:11 by lucho             #+#    #+#             */
/*   Updated: 2025/12/16 22:55:21 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_window_width(char **map)
{
	int	width;

	width = ft_strlen(map[0]);
	if (width > 0 && map[0][width - 1] == '\n')
		width --;
	return (width * 64);
}

void	free_map(char **map, int line_count)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < line_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map, game->line_count);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->textures)
		free(game->textures);
}
