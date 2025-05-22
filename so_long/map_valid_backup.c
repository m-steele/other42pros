/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_backup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:39 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/21 12:47:51 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_grid(t_map *map)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (map->y + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < map->y)
	{
		copy[y] = ft_strdup(map->grid[y]);
		if (!copy[y])
		{
			while (--y >= 0)
				free(copy[y]);
			free(copy);
			return (NULL);
		}
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

void	flood_fill(t_map *map, int x, int y, int *flood_coll, int *flood_exits)
{
	if (x < 0 || y < 0 || x >= map->x || y >= map->y)
		return ;
	if (map->grid[y][x] == 'F' || map->grid[y][x] == '1')
		return ;
	if (map->grid[y][x] == 'E')
		(*flood_exits)++;
	if (map->grid[y][x] == 'C')
		(*flood_coll)++;
	map->grid[y][x] = 'F';
	flood_fill(map, x + 1, y, flood_coll, flood_exits);
	flood_fill(map, x - 1, y, flood_coll, flood_exits);
	flood_fill(map, x, y + 1, flood_coll, flood_exits);
	flood_fill(map, x, y - 1, flood_coll, flood_exits);
}

static int	tile_valid(t_map *map, int x, int y, int *player, int *exit, int *collect)
{
	char	c = map->grid[y][x];
	
	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
		return (0);
	if (c == 'P')
	{
		(*player)++;
		map->player_x = x;
		map->player_y = y;
	}
	if (c == 'E')
		(*exit)++;
	if (c == 'C')
		(*collect)++;
	return (1);
}

static int	line_valid(t_map *map, int y, int *player, int *exit, int *collect)
{
	int		x;
	
	x = -1;
	while (++x < map->x)
	{
		if (!tile_valid(map, x, y, player, exit, collect))
			return (0);
		if ((y == 0 || y == map->y - 1 || x == 0 ||
			x == map->x - 1) && map->grid[y][x] != '1')
			return (0);
	}
	if ((int)ft_strlen(map->grid[y]) != map->x)
		return (0);
	return (1);
}

static void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(grid[i++]);
	free(grid);
}

void	print_map(t_map *map)
{
	int	y = 0;
	while (y < map->y)
	{
		ft_printf("%s\n", map->grid[y]);
		y++;
	}	
}

/*Seems that we can get rid of collect since it is already stored in colect_count
Then it might be best to make a struct for other things line the flood counts
BUT can we at least store these in the map struct? I do not see why we cannot*/

int	map_valid(t_map *map)
{
	int		y;
	int		player;
	int		exit;
	int		collect; /*This is already stored in map as collect_count*/
	int		flood_coll;
	int		flood_exits;
	char	**grid_copy;
	t_map	map_copy;

	y = -1;
	player = 0;
	exit = 0;
	collect = 0;
	flood_coll = 0;
	flood_exits = 0;
	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (0);
	map_copy = *map;
	map_copy.grid = grid_copy;
	while (++y < map->y)
		if (!line_valid(map, y, &player, &exit, &collect))
		{
			free_grid(grid_copy, map->y);
			return (0);
		}
	print_map(map);
	flood_fill(&map_copy, map->player_x, map->player_y, &flood_coll, &flood_exits);
	ft_printf("flood_coll = %d\ncollectables = %d\n", flood_coll, collect);
	print_map(&map_copy);
	free_grid(grid_copy, map->y);
	if (player !=1 || exit != 1|| collect < 1)
		return (0)	;
	if (flood_coll != collect || flood_exits != 1)
		return (0);
	return (1);
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
