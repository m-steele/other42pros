/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:36:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/06 11:55:55 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

/*gcc -I/home/peatjohnston/_42/github/other42pros/so_long/mlx -o mlx_app /home/peatjohnston/_42/github/other42pros/so_long/mlx_init.c -L/home/peatjohnston/_42/github/other42pros/so_long/mlx -lmlx -lXext -lX11 -lm -lbsd*/
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr +(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		x = 500;
	int		y = 250;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Try This");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (x > y)
	{
		my_mlx_pixel_put(&img, x, y, 255);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		x--;
		y++;
	}
	mlx_loop(mlx);
}