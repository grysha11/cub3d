/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:15 by atamas            #+#    #+#             */
/*   Updated: 2024/11/08 13:09:01 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "./minilibx/mlx_int.h"
#include "cub3d.h"

void	my_mlx_pixel_put(t_struct *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->b_p_p / 8));
	*(unsigned int *)dst = color;
}

int	clean_exit(t_struct *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int	event_handler(int keycode, t_struct *mlx)
{
	if (keycode == KEY_ESC)
	{
		clean_exit(mlx);
	}
	if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_S || keycode == KEY_W)
		movement(keycode, mlx);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate(keycode, mlx);
	clear_screen(mlx);
	draw_triangle(25, mlx->player_x, mlx->player_y, RED, mlx);
	// draw_square(50, mlx->player_x, mlx->player_y, RED, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (0);
}

int	mouse_move(int x, int y, t_struct *mlx)
{
	if (x < mlx->prev_x)
		rotate(KEY_LEFT, mlx);
	else
		rotate(KEY_RIGHT, mlx);
	mlx->prev_x = x;
	// printf("x: %d, y: %d\n", x, y);
	// my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
	clear_screen(mlx);
	draw_triangle(25, mlx->player_x, mlx->player_y, RED, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (y - y);
}

int	mlx_setup(t_struct *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (write(2, "Failed to initalize mlx!\n", 25), 1);
	mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_X, SCREEN_Y, "Cub3D");
	if (!mlx->mlx_win)
		return (write(2, "Failed to create window!\n", 25), 1);
	mlx_hook(mlx->mlx_win, 17, 1L << 17, clean_exit, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, event_handler, mlx);
	mlx_hook(mlx->mlx_win, 6, 1L << 6, mouse_move, mlx);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_X, SCREEN_Y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->b_p_p, &mlx->line_length, &mlx->endian);
	return (0);
}
