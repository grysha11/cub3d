/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:04:07 by atamas            #+#    #+#             */
/*   Updated: 2024/11/28 11:30:57 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_struct *mlx)
{
	double	old_dx;
	double	old_plane_x;
	double	r_rad;

	if (mlx->key.r_left == true)
	{
		r_rad = mlx->rotate_speed * PI / 180.0;
		old_dx = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(-r_rad) - mlx->dir_y * sin(-r_rad);
		mlx->dir_y = old_dx * sin(-r_rad) + mlx->dir_y * cos(-r_rad);
		old_plane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(-r_rad) - mlx->plane_y * sin(-r_rad);
		mlx->plane_y = old_plane_x * sin(-r_rad) + mlx->plane_y * cos(-r_rad);
	}
	if (mlx->key.r_right == true)
	{
		r_rad = mlx->rotate_speed * PI / 180.0;
		old_dx = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(r_rad) - mlx->dir_y * sin(r_rad);
		mlx->dir_y = old_dx * sin(r_rad) + mlx->dir_y * cos(r_rad);
		old_plane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(r_rad) - mlx->plane_y * sin(r_rad);
		mlx->plane_y = old_plane_x * sin(r_rad) + mlx->plane_y * cos(r_rad);
	}
}

int	is_wall(t_struct *mlx, double x, double y)
{
	return (mlx->parse->map[(int)floor(y)][(int)floor(x)] == '1');
}

void	can_move(t_struct *mlx, double new_x, double new_y)
{
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;

	x_min = new_x - 0.1;
	x_max = new_x + 0.1;
	y_min = new_y - 0.1;
	y_max = new_y + 0.1;
	if (!is_wall(mlx, x_min, y_min) && !is_wall(mlx, x_min, y_max)
		&& !is_wall(mlx, x_max, y_min) && !is_wall(mlx, x_max, y_max))
	{
		mlx->player_x = new_x;
		mlx->player_y = new_y;
	}
}

void	movement(t_struct *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player_x;
	new_y = mlx->player_y;
	if (mlx->key.left == true)
	{
		new_x -= mlx->plane_x * mlx->move_speed;
		new_y -= mlx->plane_y * mlx->move_speed;
	}
	if (mlx->key.right == true)
	{
		new_x += mlx->plane_x * mlx->move_speed;
		new_y += mlx->plane_y * mlx->move_speed;
	}
	if (mlx->key.forward == true)
	{
		new_x += mlx->dir_x * mlx->move_speed;
		new_y += mlx->dir_y * mlx->move_speed;
	}
	if (mlx->key.backward == true)
	{
		new_x -= mlx->dir_x * mlx->move_speed;
		new_y -= mlx->dir_y * mlx->move_speed;
	}
	can_move(mlx, new_x, new_y);
}
