/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:39 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/19 09:24:48 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	tile_valid(char c, int *player, int *exit, int *collect)
{
	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
		return (0);
	if (c == 'P')
		(*player)++;
	if (c == 'E')
		(*exit)++;
	if (c == 'C')
		(*collect)++;
	return (1);
}

static int	line_valid(t_map *map, int y, int *player, int *exit, int *collect)
{
	char	c;
	int		x;
	
	x = -1;
	while (++x < map->x)
	{
		c = map->grid[y][x];
		if (!tile_valid(c, player, exit, collect))
			return (0);
		if ((y == 0 || y == map->y - 1 || x == 0 ||
			x == map->x - 1) && c != '1')
			return (0);
	}
	if ((int)ft_strlen(map->grid[y]) != map->x)
		return (0);
	return (1);
}

int	map_valid(t_map *map)
{
	int		y;
	int		player;
	int		exit;
	int		collect;

	y = -1;
	player = 0;
	exit = 0;
	collect = 0;
	while (++y < map->y)
		if (!line_valid(map, y, &player, &exit, &collect))
			return (0);
	return (player == 1 && exit ==1 && collect >= 1);
}

/*THIS IS THE ORIGINAL THAT IS TOO BIG
THE ABOVE APPEARS TO BE FINE FOR NOW...*/
// int	map_valid(t_map *map)
// {
// 	int		x;
// 	int		y;
// 	int		player = 0;
// 	int		exit = 0;
// 	int		collectable = 0;
// 	char	tile;

// 	y = -1;
// 	while (++y < map->y)
// 	{
// 		x = -1;
// 		while (++x < map->x)
// 		{
// 			tile = map->grid[y][x];
// 			if (tile != '0' && tile != '1' && tile != 'P' && tile != 'E' && tile != 'C')
// 				return (0);
// 			if (tile == 'P')
// 				player++;
// 			if (tile == 'E')
// 				exit++;
// 			if (tile == 'C')
// 				collectable++;
// 			if (y == 0 || y == map->y - 1 || x == 0 || x == map->x -1)
// 			{
// 				if (tile != '1')
// 					return (0);
// 			}
// 		}
// 		if ((int)ft_strlen(map->grid[y]) != map->x)
// 			return (0);
// 	}
// 	if (player != 1 || exit != 1 || collectable < 1)
// 		return (0);
// 	return (1);
// }
