/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:39:06 by atamas            #+#    #+#             */
/*   Updated: 2024/12/06 11:25:11 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	line_height(t_ray *ray)
{
	ray->line_height = (int)(SCREEN_Y / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + SCREEN_Y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_Y / 2;
	if (ray->draw_end >= SCREEN_Y)
		ray->draw_end = SCREEN_Y - 1;
}

void	choose_img_side(t_ray *ray, t_struct *mlx)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			ray->t = mlx->texture[WE];
		else
			ray->t = mlx->texture[EA];
	}
	else
	{
		if (ray->ray_dir_y < 0)
			ray->t = mlx->texture[SO];
		else
			ray->t = mlx->texture[NO];
	}
}
