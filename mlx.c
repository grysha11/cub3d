/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:15 by atamas            #+#    #+#             */
/*   Updated: 2024/11/04 15:30:57 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "./minilibx/mlx_int.h"
#include "cub3d.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

void	my_mlx_pixel_put(t_struct *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_screen(t_struct *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SCREEN_Y)
	{
		j = 0;
		while (j < SCREEN_X)
		{
			j++;
			my_mlx_pixel_put(mlx, j, i, 0);
		}
		i++;
	}
}

void	draw_square(int size, int x, int y, int color, t_struct *game)
{
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x + i, y, color);
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x, y + i, color);
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x + size, y + i, color);
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x + i, y + size, color);
}

void	draw_line(t_struct *mlx, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		if (x0 >= 0 && x0 < SCREEN_X && y0 >= 0 && y0 < SCREEN_Y)
			my_mlx_pixel_put(mlx, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_triangle(int size, int x, int y, int color, t_struct *mlx)
{
	double	angle = atan2(mlx->dir_y, mlx->dir_x);
	double	half_base = size / 2.0;
	double	height = size * 1.5;

	// Calculate the vertices of the triangle
	int v1_x = x + height * cos(angle);
	int v1_y = y + height * sin(angle);
	int v2_x = x - half_base * cos(angle + PI / 2);
	int v2_y = y - half_base * sin(angle + PI / 2);
	int v3_x = x + half_base * cos(angle + PI / 2);
	int v3_y = y + half_base * sin(angle + PI / 2);

	// Draw lines between the vertices
	draw_line(mlx, v1_x, v1_y, v2_x, v2_y, color);
	draw_line(mlx, v2_x, v2_y, v3_x, v3_y, color);
	draw_line(mlx, v3_x, v3_y, v1_x, v1_y, color);
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
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_speed_rad;

	if (keycode == KEY_ESC)
	{
		clean_exit(mlx);
	}
	if (keycode == KEY_A)
	{
		mlx->player_x -= mlx->plane_x * mlx->move_speed;
		mlx->player_y -= mlx->plane_y * mlx->move_speed;
	}
	if (keycode == KEY_D)
	{
		mlx->player_x += mlx->plane_x * mlx->move_speed;
		mlx->player_y += mlx->plane_y * mlx->move_speed;
	}
	if (keycode == KEY_W)
	{
		mlx->player_x += mlx->dir_x * mlx->move_speed;
		mlx->player_y += mlx->dir_y * mlx->move_speed;
	}
	if (keycode == KEY_S)
	{
		mlx->player_x -= mlx->dir_x * mlx->move_speed;
		mlx->player_y -= mlx->dir_y * mlx->move_speed;
	}
	if (keycode == KEY_LEFT)
	{
		rotate_speed_rad = mlx->rotate_speed * PI / 180.0;
		old_dir_x = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(-rotate_speed_rad) - mlx->dir_y * sin(-rotate_speed_rad);
		mlx->dir_y = old_dir_x * sin(-rotate_speed_rad) + mlx->dir_y * cos(-rotate_speed_rad);
		old_plane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(-rotate_speed_rad) - mlx->plane_y * sin(-rotate_speed_rad);
		mlx->plane_y = old_plane_x * sin(-rotate_speed_rad) + mlx->plane_y * cos(-rotate_speed_rad);
	}
	if (keycode == KEY_RIGHT)
	{
		rotate_speed_rad = mlx->rotate_speed * PI / 180.0;
		old_dir_x = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(rotate_speed_rad) - mlx->dir_y * sin(rotate_speed_rad);
		mlx->dir_y = old_dir_x * sin(rotate_speed_rad) + mlx->dir_y * cos(rotate_speed_rad);
		old_plane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(rotate_speed_rad) - mlx->plane_y * sin(rotate_speed_rad);
		mlx->plane_y = old_plane_x * sin(rotate_speed_rad) + mlx->plane_y * cos(rotate_speed_rad);
	}
	clear_screen(mlx);
	draw_triangle(25, mlx->player_x, mlx->player_y, RED, mlx);
	// draw_square(50, mlx->player_x, mlx->player_y, RED, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (0);
}

int	mouse_move(int x, int y, t_struct *mlx)
{
	printf("x: %d, y: %d\n", x, y);
	// my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (0);
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
	// mlx_hook(mlx->mlx_win, 6, 1L << 6, mouse_move, mlx);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_X, SCREEN_Y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	return (0);
}

int	main(void)
{
	t_struct	mlx;

	mlx.player_x = SCREEN_X / 2;
	mlx.player_y = SCREEN_Y / 2;
	mlx.dir_x = 0;
	mlx.dir_y = -1;
	mlx.plane_x = 0.66;
	mlx.plane_y = 0;
	mlx.move_speed = 5;
	mlx.rotate_speed = 3;
	// set which box in the map are we in
	if (mlx_setup(&mlx))
		return (1);
	draw_triangle(25, mlx.player_x, mlx.player_y, RED, &mlx);
	// draw_square(50, mlx.player_x, mlx.player_y, RED, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	return (0);
}
