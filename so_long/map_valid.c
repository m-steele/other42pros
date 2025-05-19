/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:39 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/19 13:58:57 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_map map, int x, int y, int *flood_coin)
{
	if (x < 0 || y < 0 || x >= map.x || y >= map.y)
		return ;
	if (map.grid[y][x] == 'F' || map.grid[y][x] == '1')
		return ;
	if (map.grid[y][x] == 'C')
		(*flood_coin)++;
	if (map.grid[y][x] != 'E')
		map.grid[y][x] = 'F';
	flood_fill(map, x + 1, y, flood_coin);
	flood_fill(map, x - 1, y, flood_coin);
	flood_fill(map, x, y + 1, flood_coin);
	flood_fill(map, x, y - 1, flood_coin);
}

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

void	print_map(t_map *map)
{
	int	y = 0;
	while (y < map->y)
	{
		ft_printf("s%\n", map->grid[y]);
		y++;
	}	
}

int	map_valid(t_map *map)
{
	int		y;
	int		player;
	int		exit;
	int		collect;
	int		flood_coin;

	y = -1;
	player = 0;
	exit = 0;
	collect = 0;
	flood_coin = 0;
	while (++y < map->y)
		if (!line_valid(map, y, &player, &exit, &collect))
			return (0);
	print_map(map);
	flood_fill(*map, map->x, map->y, &flood_coin);
	ft_printf("flood_coins = %i\ncollectables = %i\n", flood_coin, collect);
	print_map(map);
	if (flood_coin != collect)
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
