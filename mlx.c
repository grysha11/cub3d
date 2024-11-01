/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:15 by atamas            #+#    #+#             */
/*   Updated: 2024/11/01 15:47:40 by atamas           ###   ########.fr       */
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
	*(unsigned int*)dst = color;
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

void draw_square(int size, int x, int y, int color, t_struct *game)
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

void	draw_triangle(int size, int x, int y, int color, t_struct *mlx)
{
	int	i;
	int	start_x;
	int	end_x;
	int	height;
	int	j;

	i = 0;
	start_x = 0;
	end_x = 0;
	height = 0;
	j = 0;
	y = y - size / 2;
	height = (int)(size * sin((85) * PI / 180.0));
	while (i < height)
	{
		start_x = x - (i * size) / height / 2;
		end_x = x + (i * size) / height / 2;
		j = start_x;
		while (j <= end_x)
		{
			if (j >= 0 && j < SCREEN_X && (y + i) >= 0 && (y + i) < SCREEN_Y)
				my_mlx_pixel_put(mlx, j, y + i, color);
			j++;
		}
		i++;
	}
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
	double	oldDirX;
	double	oldPlaneX;
	if (keycode == KEY_ESC)
	{
		clean_exit(mlx);
	}
	if (keycode == KEY_A)
	{
		mlx->player_x -= mlx->move_speed;
		clear_screen(mlx);
		draw_square(50, mlx->player_x, mlx->player_y, RED, mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	}
	if (keycode == KEY_D)
	{
		mlx->player_x += mlx->move_speed;
		// mlx->player_y += 1;
		clear_screen(mlx);
		draw_square(50, mlx->player_x, mlx->player_y, RED, mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	}
	if (keycode == KEY_W)
	{
		mlx->player_x += mlx->dir_x * mlx->move_speed;
		mlx->player_y += mlx->dir_y * mlx->move_speed;
		clear_screen(mlx);
		draw_square(50, mlx->player_x, mlx->player_y, RED, mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	}
	if (keycode == KEY_S)
	{
		mlx->player_x -= mlx->dir_x * mlx->move_speed;
		mlx->player_y -= mlx->dir_y * mlx->move_speed;
		clear_screen(mlx);
		draw_square(50, mlx->player_x, mlx->player_y, RED, mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	}
	if (keycode == KEY_RIGHT)
	{
		oldDirX = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(-mlx->rotate_speed) - mlx->dir_y * sin(-mlx->rotate_speed);
		mlx->dir_y = oldDirX * sin(-mlx->rotate_speed) + mlx->dir_y * cos(-mlx->rotate_speed);
		oldPlaneX = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(-mlx->rotate_speed) - mlx->plane_y * sin(-mlx->rotate_speed);
		mlx->plane_y = oldPlaneX * sin(-mlx->rotate_speed) + mlx->plane_y * cos(-mlx->rotate_speed);
		printf("dir_x: %f, dir_y: %f\n", mlx->dir_x, mlx->dir_y);
	}
	if (keycode == KEY_LEFT)
	{
		oldDirX = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(mlx->rotate_speed) - mlx->dir_y * sin(mlx->rotate_speed);
		mlx->dir_y = oldDirX * sin(mlx->rotate_speed) + mlx->dir_y * cos(mlx->rotate_speed);
		oldPlaneX = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(mlx->rotate_speed) - mlx->plane_y * sin(mlx->rotate_speed);
		mlx->plane_y = oldPlaneX * sin(mlx->rotate_speed) + mlx->plane_y * cos(mlx->rotate_speed);
		printf("dir_x: %f, dir_y: %f\n", mlx->dir_x, mlx->dir_y);
	}
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
	mlx.dir_x = -1;
	mlx.dir_y = 0;
	mlx.plane_x = 0;
	mlx.plane_y = 0.66;
	mlx.move_speed = 5;
	mlx.rotate_speed = 3;
	// set which box in the map are we in
	if (mlx_setup(&mlx))
		return (1);
	draw_square(50, mlx.player_x, mlx.player_y, RED, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	return (0);
}
