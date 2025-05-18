/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:40:54 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/18 12:32:28 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	destroy_images(t_game *game)
{
	if (game->mlx)
	{
		if (game->image.space)
			mlx_destroy_image(game->mlx, game->image.space);
		if (game->image.wall)
			mlx_destroy_image(game->mlx, game->image.wall);
		if (game->image.player)
			mlx_destroy_image(game->mlx, game->image.player);
		if (game->image.exit)
			mlx_destroy_image(game->mlx, game->image.exit);
		if (game->image.collectable)
			mlx_destroy_image(game->mlx, game->image.collectable);
	}
}

void	norm_sux(t_game *game)
{
	destroy_images(game);
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

void	clean_and_exit(t_game *game, const char *error)
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
