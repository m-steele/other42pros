/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:39 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/22 11:37:39 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(grid[i++]);
	free(grid);
}

void	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->x || y >= map->y)
		return ;
	if (map->grid[y][x] == 'F' || map->grid[y][x] == '1')
		return ;
	if (map->grid[y][x] == 'E')
		map->flood_exit++;
	if (map->grid[y][x] == 'C')
		map->flood_coll++;
	map->grid[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static int	tile_valid(t_map *map, int x, int y)
{
	char	c;

	c = map->grid[y][x];
	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
		return (0);
	if (c == 'P')
	{
		map->player_count++;
		map->player_x = x;
		map->player_y = y;
	}
	if (c == 'E')
		map->exit_count++;
	return (1);
}

static int	line_valid(t_map *map, int y)
{
	int		x;

	x = -1;
	while (++x < map->x)
	{
		if (!tile_valid(map, x, y))
			return (0);
		if ((y == 0 || y == map->y - 1 || x == 0 || x == map->x - 1)
			&& map->grid[y][x] != '1')
			return (0);
	}
	if ((int)ft_strlen(map->grid[y]) != map->x)
		return (0);
	return (1);
}

int	map_valid(t_map *map)
{
	int		y;
	char	**grid_copy;
	t_map	map_copy;

	y = -1;
	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (0);
	map_copy = *map;
	map_copy.grid = grid_copy;
	while (++y < map->y)
		if (!line_valid(map, y))
			return (free_grid(grid_copy, map->y), 0);
	flood_fill(&map_copy, map->player_x, map->player_y);
	free_grid(grid_copy, map->y);
	if (map->player_count != 1 || map->exit_count != 1
		|| map->collect_count < 1)
		return (0);
	if (map_copy.flood_coll != map->collect_count || map_copy.flood_exit != 1)
		return (0);
	return (1);
}
