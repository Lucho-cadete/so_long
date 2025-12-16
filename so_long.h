/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:34:12 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/16 13:10:22 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <MLX42/MLX42.h>

typedef struct s_textures
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	mlx_image_t	*exit_closed;
	mlx_image_t	*exit_open;
}	t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	t_textures	*textures;
	char		**map;
	int			line_count;
	int			player_x;
	int			player_y;
	int			moves;
}	t_game;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_flood_data
{
	int	count_c;
	int	found_e;
}	t_flood_data;

typedef struct s_maps
{
	char	**original;
	char	**visited;
	int		width;
	int		height;
}	t_maps;

typedef struct s_map_elements
{
	int	space;
	int	exit;
	int	player;
	int	collectible;
}	t_map_elements;

/*MLX42*/

void	start_game(char **map, int line_count);
int		calculate_window_width(char **map);
t_game	init_game_struct(mlx_t *mlx, char **map, int line_count, t_textures *tex);
void	free_textures(mlx_t *mlx, t_textures *textures);

/*Main part*/
int		count_lines(int fd);
char	**read_map(int fd, int line_count);

/*MAP*/

int		is_rectangular(char **map, int line_count);
int		check_horizontal_wall(char *line);
int		check_vertical_walls(char **map, int line_count, size_t width);
int		is_closed(char **map, int line_count);
int		check_map_elements(char **map, int line_count);
int		validate_elements(t_map_elements *elements);
int		elements_each_line(char *line, t_map_elements *elements, size_t width);

/*PATH*/

int		count_c(char **map, int line_count);
void	find_player(char **map, int line_count, int *x, int *y);
void	fill_line_with_ceros(char *line, int width);
char	**create_parallel_map(int line_count, int width);
int		validate_path(char **map, int line_count);
int		setup_flood_fill(char **map, int line_count, t_maps *maps, t_position *player);
void	flood_fill(t_maps *maps, int x, int y, t_flood_data *data);

/*GNL*/

char	*extract_line(char *rest);
char	*extract_rest(char *rest);
char	*add_rest(char *rest, char *buffer);
int		read_and_update_rest(int fd, char **rest);
char	*get_next_line(int fd);
size_t	ft_strlen_and_find_newline(const char *str, int *find_newline);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

/*LIBFT*/

void	ft_putstr_fd(char *s, int fd);

/*Extra tools*/

size_t	ft_strlen(const char *str);