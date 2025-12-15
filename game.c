/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:34:12 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/14 22:41:40 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void render_map(mlx_t *mlx, char **map, int line_count, t_textures *tex)
{
    int j;
    int i;
    
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
            else if (map[j][i] == 'E')
                mlx_image_to_window(mlx, tex->exit, i * 64, j * 64);
            i++;
        }
        j++;
    }
}

mlx_image_t *load_single_texture(mlx_t *mlx, char *path)
{
    mlx_texture_t *texture;
    mlx_image_t *image;
    
    texture = mlx_load_png(path);
    if (!texture)
        return (NULL);
    
    image = mlx_texture_to_image(mlx, texture);
    mlx_delete_texture(texture);
    
    return (image);
}

t_textures *load_textures(mlx_t *mlx)
{
    t_textures *textures;
    
    textures = malloc(sizeof(t_textures));
    if (!textures)
        return (NULL);
    
    textures->wall = load_single_texture(mlx, "textures/wall.png");
    textures->floor = load_single_texture(mlx, "textures/floor.png");
    textures->player = load_single_texture(mlx, "textures/player.png");
    textures->collectible = load_single_texture(mlx, "textures/collectible.png");
    textures->exit = load_single_texture(mlx, "textures/exit.png");
    
    return (textures);
}

void execute_new_movement(t_game *game, int new_x, int new_y)
{
	// char tile;

	// tile = game->map[new_y][new_x];
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_y = new_y;
	game->player_x = new_x;
	game->moves++;
	// if (tile == 'C')
	// 	handle_collectibles(game);
	// if (tile == 'E')
	// 	check_victory(game);
	printf ("Number of moves: %d\n", game->moves);
	render_map(game->mlx, game->map, game->line_count, game->textures);
	return;
}

void calculate_new_position(mlx_key_data_t keydata, t_game *game, int *new_x, int *new_y)
{
	*new_x = game->player_x;
	*new_y = game->player_y;

	if (keydata.key == MLX_KEY_W)
		(*new_y)--;
	else if (keydata.key == MLX_KEY_S)
		(*new_y)++;
	else if (keydata.key == MLX_KEY_A)
		(*new_x)--;
	else if (keydata.key == MLX_KEY_D)
		(*new_x)++;
	return;
}

void handler_movement(mlx_key_data_t keydata, t_game *game)
{
	int new_x;
	int new_y;

	calculate_new_position(keydata, game, &new_x, &new_y);
	if (game->map[new_y][new_x] != '1')
		execute_new_movement(game, new_x, new_y);
}

void key_handler(mlx_key_data_t keydata, void *param)
{
    t_game *game;
	// int new_x;
	// int new_y;
	// int moved;
    
	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    	mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS)
		handler_movement(keydata, game);
}

int calculate_window_width(char **map)
{
	int width;
	
	width = ft_strlen(map[0]);
	if (width > 0 && map[0][width - 1] == '\n')
		width --;
	return (width * 64);
}

t_game init_game_struct(mlx_t *mlx, char **map, int line_count, t_textures *tex)
{
	t_game game;

	game.mlx = mlx;
	game.textures = tex;
	game.map = map;
	game.line_count = line_count;
	find_player(map, line_count, &game.player_x, &game.player_y);
	game.moves = 0;
	return (game);
}

void start_game(char **map, int line_count)
{
    mlx_t *mlx;
    t_textures *textures;
	t_game game;
    int window_width;
    int window_height;
    
	window_width = calculate_window_width(map);
    window_height = 64 * line_count;
    mlx = mlx_init(window_width, window_height, "so_long", false);
    if (!mlx)
        return;
    textures = load_textures(mlx);
    if (!textures)
    {
        mlx_terminate(mlx);
        return;
    }
	game = init_game_struct(mlx, map, line_count, textures);
	render_map(game.mlx, game.map, game.line_count, game.textures);
    mlx_key_hook(game.mlx, key_handler, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
}
