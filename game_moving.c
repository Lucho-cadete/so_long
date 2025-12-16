/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_moving.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:49:11 by lucho             #+#    #+#             */
/*   Updated: 2025/12/16 22:55:08 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	execute_new_movement(t_game *game, int new_x, int new_y)
{
	char	tile;

	tile = game->map[new_y][new_x];
	if (tile == 'E')
	{
		if (count_c(game->map, game->line_count) == 0)
		{
			render_map(game->mlx, game->map, game->line_count, game->textures);
			printf("🎉 YOU WIN! Moves: %d\n", game->moves);
			cleanup_game(game);
			exit (0);
		}
		else
			return ;
	}
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_y = new_y;
	game->player_x = new_x;
	game->moves++;
	printf ("Move number: %d\n", game->moves);
	render_map(game->mlx, game->map, game->line_count, game->textures);
	return ;
}

void	calculate_new_position(mlx_key_data_t keydata,
		t_game *game, int *new_x, int *new_y)
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
	return ;
}

void	handler_movement(mlx_key_data_t keydata, t_game *game)
{
	int	new_x;
	int	new_y;

	calculate_new_position(keydata, game, &new_x, &new_y);
	if (game->map[new_y][new_x] != '1')
		execute_new_movement(game, new_x, new_y);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		cleanup_game(game);
		exit (0);
	}
	if (keydata.action == MLX_PRESS)
		handler_movement(keydata, game);
}
