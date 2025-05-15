/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:39 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/15 12:42:12 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_valid(t_map *map)
{
	int		x;
	int		y;
	int		player = 0;
	int		exit = 0;
	int		collectable = 0;
	char	tile;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			tile = map->grid[y][x];
			if (tile != '0' && tile != '1' && tile != 'P' && tile != 'E' && tile != 'C')
				return (0);
			if (tile == 'P')
				player++;
			if (tile == 'E')
				exit++;
			if (tile == 'C')
				collectable++;
			if (y == 0 || y == map->y - 1 || x == 0 || x == map->x -1)
			{
				if (tile != '1')
					return (0);
			}
		}
		if ((int)ft_strlen(map->grid[y]) != map->x)
			return (0);
	}
	if (player != 1 || exit != 1 || collectable < 1)
		return (0);
	return (1);
}
