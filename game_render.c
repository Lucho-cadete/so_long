/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:47:50 by lucho             #+#    #+#             */
/*   Updated: 2025/12/16 22:48:20 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_exit(mlx_t *mlx, t_textures *tex, int i, int j)
{
	mlx_image_to_window(mlx, tex->exit_closed, i * 64, j * 64);
}

void	render_exit_open(mlx_t *mlx, t_textures *tex, int i, int j)
{
	mlx_image_to_window(mlx, tex->exit_open, i * 64, j * 64);
}

void	render_map(mlx_t *mlx, char **map, int line_count, t_textures *tex)
{
	int	j;
	int	i;

	j = 0;
	while (j < line_count)
	{
		i = 0;
		while (map[j][i] != '\n' && map[j][i] != '\0')
		{
			if (map[j][i] == '1')
				mlx_image_to_window(mlx, tex->wall, i * 64, j * 64);
			else if (map[j][i] == '0')
				mlx_image_to_window(mlx, tex->floor, i * 64, j * 64);
			else if (map[j][i] == 'P')
				mlx_image_to_window(mlx, tex->player, i * 64, j * 64);
			else if (map[j][i] == 'C')
				mlx_image_to_window(mlx, tex->collectible, i * 64, j * 64);
			else if (map[j][i] == 'E' && count_c(map, line_count) > 0)
				render_exit(mlx, tex, i, j);
			else if (map[j][i] == 'E')
				render_exit_open(mlx, tex, i, j);
			i++;
		}
		j++;
	}
}
