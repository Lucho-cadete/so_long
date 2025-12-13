/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:58:18 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/12 21:11:41 by lucho            ###   ########.fr       */
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

void flood_fill(t_maps *maps, int x, int y, t_flood_data *data)
{
    // === CASOS BASE (condiciones de parada) ===
    
    // 1. ¿Estoy fuera de los límites?
    if (x < 0 || y < 0 || x >= maps->width || y >= maps->height)
        return;
    
    // 2. ¿Es un muro?
    if (maps->original[y][x] == '1')
        return;
    
    // 3. ¿Ya visité esta posición?
    if (maps->visited[y][x] == '1')
        return;
    
    // === PROCESAR POSICIÓN ACTUAL ===
    
    // 4. Marcar como visitado
    maps->visited[y][x] = '1';
    
    // 5. ¿Es un coleccionable?
    if (maps->original[y][x] == 'C')
        data->count_c++;
    
    // 6. ¿Es la salida?
    if (maps->original[y][x] == 'E')
        data->found_e = 1;
    
    // === CASO RECURSIVO (expandirse) ===
    
    // 7. Llamar recursivamente en 4 direcciones
    flood_fill(maps, x, y - 1, data);  // Arriba
    flood_fill(maps, x, y + 1, data);  // Abajo
    flood_fill(maps, x - 1, y, data);  // Izquierda
    flood_fill(maps, x + 1, y, data);  // Derecha
}