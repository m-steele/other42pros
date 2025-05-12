/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:40:54 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/12 12:17:00 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	key_press(int key, t_game *game)
{
	static int	i;
	
	i = 0;
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		i++;
		ft_printf("\nnumber of moves: %i\n", i);
	}
	else if (key == ESC)	/*IS THIS ESC NECESSARY HERE????*/
		close(key, game);
	return (0);
}


int	close(int key, t_game *game)
{
	if (key == ESC || key == X_CLOSE)
	{
		if (game)
		{
			if (game->win && game->mlx) // Check if window and mlx pointers are valid
			{
				mlx_destroy_window(game->mlx, game->win);
				game->win = NULL; // Set to NULL after destroying to prevent double free
			}
			if (game->mlx) // Check if mlx pointer is valid
			{
				mlx_destroy_display(game->mlx); // Crucial for cleaning up X server connection and resources
				free(game->mlx);                // Free the memory allocated by mlx_init()
				game->mlx = NULL; // Set to NULL after freeing
			}
		}
		exit(0); // Terminate the program
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
		return (ft_printf("Error init game"), 1);
	if (!load_map(av[1], &game.map))
		return (free(game.mlx), ft_printf("ERROR Loading map"), 1);
	game.win = mlx_new_window(game.mlx, game.map.x * T_S,
		game.map.y * T_S, "so_long");
	if (!game.win)
		return (ft_printf("Error generating window"), 1);
	if (!load_images(&game))
		return (ft_printf("Error loading images"), 1);
	render_map(&game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_hook(game.win, 17, 0, close, &game);
	mlx_loop(game.mlx);
	return (0);
}
