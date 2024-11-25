/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:04:07 by atamas            #+#    #+#             */
/*   Updated: 2024/11/25 17:00:13 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(int keycode, t_struct *mlx)
{
	double	old_dx;
	double	old_plane_x;
	double	rot_rad;

	if (keycode == KEY_LEFT)
	{
		rot_rad = mlx->rotate_speed * PI / 180.0;
		old_dx = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(-rot_rad) - mlx->dir_y * sin(-rot_rad);
		mlx->dir_y = old_dx * sin(-rot_rad) + mlx->dir_y * cos(-rot_rad);
		old_plane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(-rot_rad) - mlx->plane_y * sin(-rot_rad);
		mlx->plane_y = old_plane_x * sin(-rot_rad) + mlx->plane_y * cos(-rot_rad);
	}
	if (keycode == KEY_RIGHT)
	{
		rot_rad = mlx->rotate_speed * PI / 180.0;
		old_dx = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(rot_rad) - mlx->dir_y * sin(rot_rad);
		mlx->dir_y = old_dx * sin(rot_rad) + mlx->dir_y * cos(rot_rad);
		old_plane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(rot_rad) - mlx->plane_y * sin(rot_rad);
		mlx->plane_y = old_plane_x * sin(rot_rad) + mlx->plane_y * cos(rot_rad);
	}
}

int is_wall(t_struct *mlx, double x, double y)
{
	return mlx->parse->map[(int)floor(y)][(int)floor(x)] == '1';
}

void	can_move(t_struct *mlx, double new_x, double new_y)
{
	// double	x;
	// double	y;
	double x_min = new_x - 0.1;
	double x_max = new_x + 0.1;
	double y_min = new_y - 0.1;
	double y_max = new_y + 0.1;

	if (!is_wall(mlx, x_min, y_min) && !is_wall(mlx, x_min, y_max) &&
		!is_wall(mlx, x_max, y_min) && !is_wall(mlx, x_max, y_max))
	{
		mlx->player_x = new_x;
		mlx->player_y = new_y;
	}
	// x = new_x;
	// y = new_y;
	// printf("x is: %f y is: %f\n", x, y);
	// if (mlx->parse->map[(int)floor(y)][(int)floor(x)] != '1')
	// {
	// 	mlx->player_x = new_x;
	// 	mlx->player_y = new_y;
	// }
	// if (x > 0 && x < SCREEN_X && mlx->parse->map[inty][intx] != '1')
	// 	mlx->player_x = new_x;
	// if (y > 0 && y < SCREEN_Y && mlx->parse->map[inty][intx] != '1')
	// 	mlx->player_y = new_y;
}

void	movement(int keycode, t_struct *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player_x;
	new_y = mlx->player_y;
	if (keycode == KEY_A)
	{
		new_x -= mlx->plane_x * mlx->move_speed;
		new_y -= mlx->plane_y * mlx->move_speed;
	}
	if (keycode == KEY_D)
	{
		new_x += mlx->plane_x * mlx->move_speed;
		new_y += mlx->plane_y * mlx->move_speed;
	}
	if (keycode == KEY_W)
	{
		new_x += mlx->dir_x * mlx->move_speed;
		new_y += mlx->dir_y * mlx->move_speed;
	}
	if (keycode == KEY_S)
	{
		new_x -= mlx->dir_x * mlx->move_speed;
		new_y -= mlx->dir_y * mlx->move_speed;
	}
	can_move(mlx, new_x, new_y);
}
