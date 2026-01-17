/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 08:34:22 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/17 16:05:07 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(char **map, int line_count, int *x, int *y)
{
	int	i;
	int	j;

	j = 0;
	while (j < line_count - 1)
	{
		i = 0;
		while (map[j][i] != '\n')
		{
			if (map[j][i] == 'P')
			{
				*x = i;
				*y = j;
			}
			i++;
		}
		j++;
	}
}
