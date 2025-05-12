/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:02:27 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/12 13:00:21 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	load_images(t_game *game)
{
	int x;
	int y;

	game->image.space = mlx_xpm_file_to_image(game->mlx,
		"texture/space.xpm", &x, &y);
	game->image.space = mlx_xpm_file_to_image(game->mlx,
		"texture/wall.xpm", &x, &y);
	game->image.space = mlx_xpm_file_to_image(game->mlx,
		"texture/collectable.xpm", &x, &y);
	game->image.space = mlx_xpm_file_to_image(game->mlx,
		"texture/exit.xpm", &x, &y);
	game->image.space = mlx_xpm_file_to_image(game->mlx,
		"texture/player.xpm", &x, &y);
	if (!game->image.space || !game->image.wall || !game->image.collectable
		|| !game->image.exit || !game->image.player)
		return (0);
	return (1);
}

// use mlx_put_image_to_window() to put the images on the map
static void	put_to_win(t_game *game, char *tile, int x, int y) /*here map could just be a char?*/
{
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.wall, x, y);
	else if (tile == '0' || tile == 'C' || tile == 'E' || tile == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.space, x, y);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.collectable, x, y);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.exit, x, y);
		else if (tile == 'P')
	{
		game->map.player_x = x;
		game->map.player_x = y;
		mlx_put_image_to_window(game->mlx, game->win,
			game->image.player, x, y);
	}
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
			x++;
		}
		y++;
	}
}