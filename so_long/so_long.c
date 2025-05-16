/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:40:54 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/16 09:17:31 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	key_count(int key, t_game **game)
{
	static int	i;
	
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		i++;
		ft_printf("number of moves: %i\n", i);
	}
	else if (key == ESC)
		close_g(key, *game);
	return (i);
}





/*Something is very wrong with the mechanics of movement*/
/*Can almost get it to work, but why it walks into walls and resets 
at starting position? --> becuase it is not updated when hitting wall?
But why will it not exit the game as I have demo'd here????*/
void move_player(int new_x, int new_y, t_game *game)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map.grid[new_y][new_x] = '0';
		game->map.grid[new_y][new_x] = 'P';
		ft_printf("Num Horror Idels: %i, Idles Collected: %i\n", game->map.collect_count, game->collected);
	}
	if (game->map.grid[new_y][new_x] == '0')
		game->map.grid[new_y][new_x] = 'P';
	if (game->map.grid[new_y][new_x] == '1')
	{
		ft_printf("You May not cross the Walls of Hell, YOU LOSE!!!");
		close_g(ESC, game);
	}
}

void	complete_level(int new_x, int new_y, t_game *game)
{
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->collected == game->map.collect_count)
		{
			ft_printf("YOU WIN!! You collected all horror idles and escaped hell.\n");
			close_g(ESC, game);
		}
		else
			ft_printf("You cannot get out of hell without all horror idles ]:{O\n");
	}
}

int	key_press(int key, t_game *game)
{
	int	new_x;
	int	new_y;
	
	new_x = game->map.player_x / T_S;
	new_y = game->map.player_y / T_S;
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT || key == ESC)
		key_count(key, &game);
	if (key == UP && game->map.grid[new_y][new_x] != '1')
		new_y--;
	else if (key == DOWN && game->map.grid[new_y][new_x] != '1')
		new_y++;
	else if (key == LEFT && game->map.grid[new_y][new_x] != '1')
		new_x--;
	else if (key == RIGHT && game->map.grid[new_y][new_x] != '1')
		new_x++;
	if (game->map.grid[new_y][new_x] != '1')
		move_player(new_x, new_y, game);
	if (game->map.grid[new_y][new_x] == 'E')
		complete_level(new_x, new_y, game);
	render_map(game);
	return (0);
}

int	close_g(int key, t_game *game)
{
	if (key == ESC || key == X_CLOSE)
	{
		if (game)
		{
			if (game->win && game->mlx)
			{
				mlx_destroy_window(game->mlx, game->win);
				game->win = NULL;
			}
			if (game->mlx)
			{
				mlx_destroy_display(game->mlx);
				free(game->mlx);
				game->mlx = NULL;
			}
		}
		exit(0);
	}
	return (0);
}

int	main(int ac,char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	if (ac != 2)
		return (ft_printf("%s\n%s maps/map.ber\n", LOAD_ER, av[0]));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_printf("Error init game\n"), 1);
	if (!load_map(av[1], &game.map))
		return (free(game.mlx), ft_printf("Error Loading map\n"), 1);

		countif game->map.image.collectable!!!!!!!!!!
	game->map.collect_count++;

	
	game.win = mlx_new_window(game.mlx, game.map.x * T_S,
		game.map.y * T_S, "so_long");
	if (!game.win)
		return (ft_printf("Error generating window\n"), 1);
	if (!load_images(&game))
		return (ft_printf("Error loading images\n"), 1);
	render_map(&game);
	mlx_hook(game.win, 17, 0, close_g, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
