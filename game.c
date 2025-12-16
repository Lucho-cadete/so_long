/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:34:12 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/16 22:54:43 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*load_single_texture(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

t_textures	*load_textures(mlx_t *mlx)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->wall = load_single_texture(mlx, "textures/wall.png");
	textures->floor = load_single_texture(mlx, "textures/floor.png");
	textures->player = load_single_texture(mlx, "textures/player.png");
	textures->collectible = load_single_texture(mlx,
			"textures/collectible.png");
	textures->exit_closed = load_single_texture(mlx,
			"textures/exit_closed.png");
	textures->exit_open = load_single_texture(mlx, "textures/exit_open.png");
	return (textures);
}

t_game	init_game_struct(mlx_t *mlx, char **map,
		int line_count, t_textures *tex)
{
	t_game	game;

	game.mlx = mlx;
	game.textures = tex;
	game.map = map;
	game.line_count = line_count;
	find_player(map, line_count, &game.player_x, &game.player_y);
	game.moves = 0;
	return (game);
}

void	start_game(char **map, int line_count)
{
	mlx_t		*mlx;
	t_textures	*textures;
	t_game		game;
	int			window_width;
	int			window_height;

	window_width = calculate_window_width(map);
	window_height = 64 * line_count;
	mlx = mlx_init(window_width, window_height, "so_long", false);
	if (!mlx)
		return ;
	textures = load_textures(mlx);
	if (!textures)
	{
		mlx_terminate(mlx);
		return ;
	}
	game = init_game_struct(mlx, map, line_count, textures);
	render_map(game.mlx, game.map, game.line_count, game.textures);
	mlx_key_hook(game.mlx, key_handler, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
}
