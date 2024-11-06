/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:04:07 by atamas            #+#    #+#             */
/*   Updated: 2024/11/05 13:25:03 by atamas           ###   ########.fr       */
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

void	movement(int keycode, t_struct *mlx)
{
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
}
