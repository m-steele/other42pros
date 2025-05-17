/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:02:27 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/17 11:09:16 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static int	m_grid(t_map *map, const char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return(0);
	map->grid = malloc(sizeof(char *) * (map->y + 1));
	if (!map->grid)
		return (close(fd), 0);
	i = 0;
	while (i < map->y)
	{
		line = get_next_line(fd);
		if (!line)
			break;
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
		return (0);
	}
		return (1);
}

int	load_map(const char *file, t_map *map)
{
	int		fd;
	char	*line;

	map->y = 0;
	map->x = 0;
	map->collect_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map->x = ft_strlen(line);
	free(line);
	while ((line = get_next_line(fd)))
	{
		int i = 0;
		map->y++; /*keep this*/
		while (line[i++])	/*this nested while/if loop needs to be delt with some other way*/
			if (line[i] == 'C')
				map->collect_count++;
		free(line); /*keep this*/
	}
	map->y++;
	close(fd);
	if (!m_grid(map, file))
		return (0);
	if (!map_valid(map))
		return (ft_printf("Error\nMap Not Valid\n"), 0);
	return (1);
}
