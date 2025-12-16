/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:54:51 by luimarti          #+#    #+#             */
/*   Updated: 2025/12/16 23:11:07 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_c(char **map, int line_count)
{
	int	counter;
	int	j;
	int	i;

	counter = 0;
	j = 0;
	while (j < line_count)
	{
		i = 0;
		while (map[j][i] != '\n' && map[j][i] != '\0')
		{
			if (map[j][i] == 'C')
				counter++;
			i++;
		}
		j++;
	}
	return (counter);
}

int	is_rectangular(char **map, int line_count)
{
	size_t	reference;
	size_t	len;
	int		i;

	reference = ft_strlen(map[0]);
	if (reference > 0 && map[0][reference - 1] == '\n')
		reference--;
	i = 1;
	while (i < line_count)
	{
		len = ft_strlen (map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			len--;
		if (len != reference)
			return (0);
		else
			i++;
	}
	return (1);
}

int	elements_each_line(char *line, t_map_elements *elements, size_t width)
{
	size_t	i;

	i = 0;
	while (i < width)
	{
		if (line[i] == 'E')
			elements->exit++;
		else if (line[i] == 'P')
			elements->player++;
		else if (line[i] == '0')
			elements->space++;
		else if (line[i] == 'C')
			elements->collectible++;
		else if (line[i] == '1')
			;
		else
		{
			ft_putstr_fd ("Error: Invalid element detected!\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_elements(t_map_elements *elements)
{
	if (elements->exit != 1 || elements->player != 1)
		return (0);
	if (elements->space < 1 || elements->collectible < 1)
		return (0);
	return (1);
}

int	check_map_elements(char **map, int line_count)
{
	int				j;
	size_t			width;
	t_map_elements	elements;

	j = 1;
	width = ft_strlen(map[0]);
	elements = (t_map_elements){0};
	if (width > 0 && map[0][width - 1] == '\n')
		width--;
	while (j < line_count - 1)
	{
		if (!elements_each_line(map[j], &elements, width))
			return (0);
		j++;
	}
	if (!validate_elements(&elements))
		return (0);
	return (1);
}
