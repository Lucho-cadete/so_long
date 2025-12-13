/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:34:12 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/13 20:36:46 by lucho            ###   ########.fr       */
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

void key_handler(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(mlx);
}

void start_game(char **map, int line_count)
{
    mlx_t *mlx;
    t_textures *textures;
    int width;
    int window_width;
    int window_height;
    
    width = ft_strlen(map[0]);
    if (width > 0 && map[0][width - 1] == '\n')
        width--;
    
    window_width = 64 * width;
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
	printf("textures: %p\n", textures);
	printf("wall: %p\n", textures->wall);
	printf("floor: %p\n", textures->floor);
	printf("player: %p\n", textures->player);
	printf("collectible: %p\n", textures->collectible);
	printf("exit: %p\n", textures->exit);
	render_map(mlx, map, line_count, textures);
    mlx_key_hook(mlx, &key_handler, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
}
