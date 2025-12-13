/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 08:34:12 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/12 22:52:21 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <MLX42/MLX42.h>

int main(void)
{
    mlx_t* mlx;
    
    mlx = mlx_init(800, 600, "Mi primera ventana", false);
    if (!mlx)
    {
        printf("Error al inicializar MLX\n");
        return (1);
    }
    
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (0);
}