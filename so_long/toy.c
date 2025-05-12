/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:48:06 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/12 10:34:17 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*practice*/

// gcc -g toy.c libft/*.c -Ilibft -Imlx -Lmlx -lmlx -lXext -lX11 -lm -o toy_app
//  valgrind --leak-check=full ./toy_app

#include "mlx/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC_KEY 65307 // ESC keycode for Linux X11

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

// This function now handles program exit on ESC key press.
int	handle_esc_key(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		if (vars)
		{
			if (vars->win && vars->mlx) // Check if window and mlx pointers are valid
			{
				mlx_destroy_window(vars->mlx, vars->win);
				vars->win = NULL; // Set to NULL after destroying to prevent double free
			}
			if (vars->mlx) // Check if mlx pointer is valid
			{
				mlx_destroy_display(vars->mlx); // Crucial for cleaning up X server connection and resources
				free(vars->mlx);                // Free the memory allocated by mlx_init()
				vars->mlx = NULL; // Set to NULL after freeing
			}
		}
		exit(0); // Terminate the program
	}
	return (0);
}

// int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

// int get_t(int trgb)
// {
// 	return ((trgb >> 24) & 0xFF);
// }

// int get_r(int trgb)
// {
// 	return ((trgb >> 16) & 0xFF);
// }

// int get_g(int trgb)
// {
// 	return ((trgb >> 8) & 0xFF);
// }

// int get_b(int trgb)
// {
// 	return (trgb & 0xFF);
// }

int main(void)
{
	t_vars	vars;

	vars.mlx = NULL;
	vars.win = NULL;
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		ft_printf("Error: mlx_init() failed!\n");
		return (1);
	}
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "so_long");
	if (!vars.win)
	{
		ft_printf("Error: mlx_new_window() failed!\n");
		if (vars.mlx) // Clean up mlx if window creation failed
		{
			mlx_destroy_display(vars.mlx);
			free(vars.mlx);
		}
		return (1);
	}

	// Hook for key presses, specifically to catch ESC for exiting
	// Event 2: KeyPress, Mask: (1L<<0) which is KeyPressMask
	mlx_hook(vars.win, 2, (1L<<0), handle_esc_key, &vars);
	
	// Consider adding a hook for the window's close button (DestroyNotify event 17)
	// mlx_hook(vars.win, 17, (1L<<17), handle_esc_key, &vars); // Or a dedicated close function

	// ft_printf("Starting MLX loop...\n"); // Add this to see if you reach this point
	mlx_loop(vars.mlx);

	// Cleanup code here is unlikely to be reached if exit() is called in hooks
	// ft_printf("MLX loop finished.\n"); // This line usually won't print if exiting via hook
	return (0);
}