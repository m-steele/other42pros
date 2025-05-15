/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:02:27 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/15 10:36:48 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	n_line(int fd)
{
	int 	n;
	char	*line;

	n = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		n++;
		free(line);
		// line = get_next_line(fd);
	}
	return (n);
}

static int	m_grid(t_map *map, const char *filename)
{
	int	fd;
	int	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return(0);
	map->grid = malloc(sizeof(char *) * (map->y + 1));
	if (!map->grid)
		return (close(fd), 0);
	i = 0;
	while (i < map->y)
	{
		map->grid[i] = get_next_line(fd);
		if (!map->grid[i])
		{
			while (--i >= 0)
				free(map->grid[i]);
			free(map->grid);
			close(fd);
			return (0);
		}
		i++;		
	}
	map->grid[i] = NULL;
	close(fd);
	return (1);
}

int	load_map(const char *filename, t_map *map)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	map->y = n_line(fd); /*allocate to struct*/
	close (fd);
	fd = open(filename, O_RDONLY); /*reopen to read*/
	// if (map->y == 0)
	// 	return (0);
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("gnl() FIALED\n");
		close (fd);
		return (0);
	}
	map->x = ft_strlen(line) - (line[ft_strlen(line) - 1] =='\n');
	free(line);
	close(fd);
	if (!m_grid(map, filename))
		return(0);
	return(1);
}