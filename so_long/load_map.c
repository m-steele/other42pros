/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:02:27 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/22 11:39:46 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_line_loop(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map->y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map->grid[i++] = line;
	}
	map->grid[i] = NULL;
	close(fd);
	if (i != map->y)
	{
		while (--i >= 0)
			free(map->grid[i]);
		free(map->grid);
		return ;
	}
}

static int	m_grid(t_map *map, const char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	map->grid = malloc(sizeof(char *) * (map->y + 1));
	if (!map->grid)
		return (close(fd), 0);
	get_line_loop(map, fd);
	return (1);
}

void	num_collectable(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			map->collect_count++;
		i++;
	}
}

int	make_grid_and_valid(const char *file, t_map *map)
{
	if (!m_grid(map, file))
		return (0);
	if (!map_valid(map))
	{
		ft_printf("Error\nMap Not Valid\n");
		return (0);
	}
	return (1);
}

int	load_map(const char *file, t_map *map)
{
	char	*line;
	int		fd;

	map->y = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (map->y == 0)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			map->x = ft_strlen(line);
		}
		num_collectable(map, line);
		map->y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!make_grid_and_valid(file, map))
		return (0);
	return (1);
}
