/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 07:25:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/22 10:07:29 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_count(int key, t_game **game)
{
	static int	i;

	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		i++;
		ft_printf("number of moves: %i\n", i);
	}
	else if (key == ESC)
	{
		clean_and_exit(*game, "");
		return (0);
	}
	return (i);
}

void	move_player(int new_x, int new_y, t_game *game)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map.grid[new_y][new_x] = '0';
	}
	game->map.player_x = new_x;
	game->map.player_y = new_y;
}

void	complete_level(int new_x, int new_y, t_game *game)
{
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->collected == game->map.collect_count)
		{
			ft_printf("You collected all Idles and escaped Hell!\n");
			clean_and_exit(game, "");
		}
		else
		{
			ft_printf("You cannot leave without all Idles\n");
			ft_printf("Remaining Idles = %i\n",
				game->map.collect_count - game->collected);
		}
	}
}

void	track_change(int key, int x, int y, t_game *game)
{
	if (game->map.grid[y][x] == 'E')
		complete_level(x, y, game);
	if (game->map.grid[y][x] != '1')
	{
		key_count(key, &game);
		move_player(x, y, game);
	}
}

int	key_press(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_x;
	new_y = game->map.player_y;
	if (key == UP)
		new_y--;
	else if (key == DOWN)
		new_y++;
	else if (key == LEFT)
		new_x--;
	else if (key == RIGHT)
		new_x++;
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		track_change(key, new_x, new_y, game);
	if (key == ESC)
	{
		clean_and_exit(game, "");
		return (0);
	}
	render_map(game);
	return (0);
}
