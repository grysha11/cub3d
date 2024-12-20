/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:15 by atamas            #+#    #+#             */
/*   Updated: 2024/12/06 11:25:02 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minilibx/mlx.h"
#include "../../inc/minilibx/mlx_int.h"
#include "../cub3d.h"

int	render(t_struct *mlx)
{
	movement(mlx);
	rotate(mlx);
	clear_screen(mlx);
	ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	return (0);
}

int	clean_exit(t_struct *mlx)
{
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->texture[NO].img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->texture[NO].img);
	if (mlx->texture[SO].img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->texture[SO].img);
	if (mlx->texture[EA].img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->texture[EA].img);
	if (mlx->texture[WE].img != NULL)
		mlx_destroy_image(mlx->mlx, mlx->texture[WE].img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_parse(mlx->parse);
	exit(0);
}

int	key_down(int keycode, t_struct *mlx)
{
	if (keycode == KEY_ESC)
		clean_exit(mlx);
	if (keycode == KEY_W)
		mlx->key.forward = true;
	if (keycode == KEY_S)
		mlx->key.backward = true;
	if (keycode == KEY_A)
		mlx->key.left = true;
	if (keycode == KEY_D)
		mlx->key.right = true;
	if (keycode == KEY_LEFT)
		mlx->key.r_left = true;
	if (keycode == KEY_RIGHT)
		mlx->key.r_right = true;
	return (0);
}

int	key_up(int keycode, t_struct *mlx)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D)
	{
		if (keycode == KEY_W)
			mlx->key.forward = false;
		if (keycode == KEY_S)
			mlx->key.backward = false;
		if (keycode == KEY_A)
			mlx->key.left = false;
		if (keycode == KEY_D)
			mlx->key.right = false;
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT)
			mlx->key.r_left = false;
		if (keycode == KEY_RIGHT)
			mlx->key.r_right = false;
	}
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
	mlx_hook(mlx->mlx_win, 2, 1L << 0, key_down, mlx);
	mlx_hook(mlx->mlx_win, 3, 1L << 1, key_up, mlx);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_X, SCREEN_Y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->b_p_p,
			&mlx->line_length, &mlx->endian);
	return (0);
}
