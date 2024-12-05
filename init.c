/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:47:39 by atamas            #+#    #+#             */
/*   Updated: 2024/12/05 13:17:13 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_w_or_e(t_struct *mlx)
{
	if (mlx->player_orient == 'E' || mlx->player_orient == 'W')
	{
		mlx->dir_y = 0;
		mlx->plane_x = 0;
		if (mlx->player_orient == 'W')
		{
			mlx->dir_x = -1;
			mlx->plane_y = -0.66;
		}
		else
		{
			mlx->dir_x = 1;
			mlx->plane_y = 0.66;
		}
	}
}

void	set_n_or_s(t_struct *mlx)
{
	if (mlx->player_orient == 'N' || mlx->player_orient == 'S')
	{
		mlx->dir_x = 0;
		mlx->plane_y = 0;
		if (mlx->player_orient == 'S')
		{
			mlx->plane_x = -0.66;
			mlx->dir_y = 1;
		}
		else
		{
			mlx->dir_y = -1;
			mlx->plane_x = 0.66;
		}
	}
}

void	set_up_player(t_struct *mlx)
{
	mlx->player_x = mlx->parse->x + 0.5;
	mlx->player_y = mlx->parse->y + 0.5;
	mlx->player_orient = mlx->parse->dir;
	if (mlx->player_orient == 'N' || mlx->player_orient == 'S')
		set_n_or_s(mlx);
	else if (mlx->player_orient == 'E' || mlx->player_orient == 'W')
		set_w_or_e(mlx);
	mlx->move_speed = MOVE_SPEED;
	mlx->rotate_speed = ROT_SPEED;
	mlx->prev_x = SCREEN_X / 2;
	mlx->key.backward = false;
	mlx->key.forward = false;
	mlx->key.left = false;
	mlx->key.right = false;
	mlx->key.r_left = false;
	mlx->key.r_right = false;
}
