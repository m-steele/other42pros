/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:40:54 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/17 11:08:56 by ekosnick         ###   ########.fr       */
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

void move_player(int new_x, int new_y, t_game *game)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map.grid[new_y][new_x] = '0';
		ft_printf(" - Horror Idels: %i, Idles Collected: %i\n", 
			game->map.collect_count, game->collected);
	}
	game->map.player_x = new_x * T_S;
	game->map.player_y = new_y * T_S;
}

void	complete_level(int new_x, int new_y, t_game *game)
{
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->collected == game->map.collect_count)
		{
			ft_printf("You collected all Horror Idles and escaped Hell!\n");
			close_g(ESC, game);
			}
		else
			ft_printf("You cannot leave without all Horror Idles ]:{=\n");
	}
}

void track_change(int key, int x, int y, t_game *game)
{
	if (game->map.grid[y][x] == 'E')
		complete_level(x, y, game);
	if (game->map.grid[y][x] != '1' && game->map.grid[y][x] != 'E')
	{
		key_count(key, &game);
		move_player(x, y, game);
	}
}

int	key_press(int key, t_game *game)
{
	int	new_x;
	int	new_y;
	
	new_x = game->map.player_x / T_S;
	new_y = game->map.player_y / T_S;
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
		close_g(key, game);
	render_map(game);
	return (0);
}

void	norm_sux(t_game *game)
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

static void	clean_and_exit(t_game *game, const char *error)
{
	int	i;

	if (error && *error)
		ft_printf("%s\n", error);
	if (!game)
		exit(1);
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.y)
		{
			if (game->map.grid[i])
			{
				free(game->map.grid[i]);
				game->map.grid[i] = NULL;
			}
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
	norm_sux(game);
	exit(0);
}

static int	destroyer(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	clean_and_exit(game, "");
	return (0);
}

int	close_g(int key, t_game *game)
{
	if (key == ESC)
		clean_and_exit(game, "");
	return (0);
}

int	main(int ac,char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	if (ac != 2)
		return (ft_printf("%s\n%s maps/map.ber\n", INPT_ER, av[0]));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_printf(INIT_ER), 1);
	if (!load_map(av[1], &game.map))
		return (free(game.mlx), ft_printf(LOAD_ER, 1));
	game.win = mlx_new_window(game.mlx, game.map.x * T_S,
		game.map.y * T_S, "so_long");
	if (!game.win)
		clean_and_exit(&game, GENW_ER);
	if (!load_images(&game))
		clean_and_exit(&game, IMAG_ER);
	render_map(&game);
	mlx_hook(game.win, 17, 0, destroyer, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	clean_and_exit(&game, "Unexpected Crash!\n");
	return (0);
}
