/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:49:34 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/16 12:14:37 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define	T_S 64 // TILE_SIZE
# define	WND_NAME "so_long"

# define	UP 119 // W
# define	LEFT 97 // A
# define	DOWN 115 // S
# define	RIGHT 100 // D
# define	ESC	65307 // Exit the game
# define	X_CLOSE 17 // x out the window

# define	LOAD_ER "ERROR!!! Use correct input like this:"

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char	**grid;
	// char	*line; /**/
	int		y;
	int		x;
	int		collect_count;
	int		player_x;
	int		player_y;
}	t_map;

typedef	struct s_image
{
	void	*space;
	void	*wall;
	void	*collectable;
	void	*exit;
	void	*player;
}	t_image;

typedef	struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_image	image;
	int		moves;
	int		collected;
}	t_game;

/*render_map*/

int	load_map(const char *filename, t_map *map);

void	render_map(t_game *game);
int		load_images(t_game *game);

int		close_g(int key, t_game *game);
// int		close_g(void *param);
int		key_press(int key, t_game *game);

int		map_valid(t_map *map);

#endif