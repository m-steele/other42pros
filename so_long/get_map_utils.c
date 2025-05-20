/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:14:48 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/20 09:25:36 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_images(t_game *game)
{
	int	x;
	int	y;

	game->image.space = mlx_xpm_file_to_image(game->mlx,
			"texture/space.xpm", &x, &y);
	game->image.wall = mlx_xpm_file_to_image(game->mlx,
			"texture/wall.xpm", &x, &y);
	game->image.collectable = mlx_xpm_file_to_image(game->mlx,
			"texture/collectable.xpm", &x, &y);
	game->image.exit = mlx_xpm_file_to_image(game->mlx,
			"texture/exit.xpm", &x, &y);
	game->image.player = mlx_xpm_file_to_image(game->mlx,
			"texture/player.xpm", &x, &y);
	if (!game->image.space || !game->image.wall || !game->image.collectable
		|| !game->image.exit || !game->image.player)
		return (0);
	return (1);
}

// use mlx_put_image_to_window() to put the images on the map
static void	put_to_win(t_game *game, char tile, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->image.space, x, y);
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.wall, x, y);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.exit, x, y);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.collectable, x, y);
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < game->map.y)
	{
		x = 0;
		while (x < game->map.x)
		{
			tile = game->map.grid[y][x];
			put_to_win(game, tile, x * T_S, y * T_S);
			if (game->map.grid[y][x] == 'P')
			{
				game->map.player_x = x;
				game->map.player_y = y;
				// game->map.player_x = x * T_S;
				// game->map.player_y = y * T_S;
				game->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.player,
		game->map.player_x * T_S, game->map.player_y * T_S);
}
