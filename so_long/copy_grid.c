/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:09:58 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/22 10:17:35 by ekosnick         ###   ########.fr       */
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
