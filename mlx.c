/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:15 by atamas            #+#    #+#             */
/*   Updated: 2024/11/27 19:58:50 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "./minilibx/mlx_int.h"
#include "cub3d.h"

int	clean_exit(t_struct *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, mlx->texture[NO].img);
	mlx_destroy_image(mlx->mlx, mlx->texture[SO].img);
	mlx_destroy_image(mlx->mlx, mlx->texture[EA].img);
	mlx_destroy_image(mlx->mlx, mlx->texture[WE].img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_parse(mlx->parse);
	exit(0);
}

int	key_press(int keycode, t_struct *mlx)
{
	if (keycode == KEY_ESC)
		clean_exit(mlx);
	if (keycode == KEY_W)
		mlx->key.forward = True;
	if (keycode == KEY_S)
		mlx->key.backward = True;
	if (keycode == KEY_A)
		mlx->key.left = True;
	if (keycode == KEY_D)
		mlx->key.right = True;
	if (keycode == KEY_LEFT)
		mlx->key.r_left = True;
	if (keycode == KEY_RIGHT)
		mlx->key.r_right = True;
	clear_screen(mlx);
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (0);
}

int	key_up(int keycode, t_struct *mlx)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D)
	{
		if (keycode == KEY_W)
			mlx->key.forward = False;
		if (keycode == KEY_S)
			mlx->key.backward = False;
		if (keycode == KEY_A)
			mlx->key.left = False;
		if (keycode == KEY_D)
			mlx->key.right = False;
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT)
			mlx->key.r_left = False;
		if (keycode == KEY_RIGHT)
			mlx->key.r_right = False;
	}
	clear_screen(mlx);
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (0);
}

int	event_handler(int keycode, t_struct *mlx)
{
	if (keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_S || keycode == KEY_W)
		movement(keycode, mlx);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate(keycode, mlx);
	clear_screen(mlx);
	ray_cast(mlx);
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
	clear_screen(mlx);
	ray_cast(mlx);
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
	// mlx_hook(mlx->mlx_win, 6, 1L << 6, mouse_move, mlx);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_X, SCREEN_Y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->b_p_p,
			&mlx->line_length, &mlx->endian);
	return (0);
}
