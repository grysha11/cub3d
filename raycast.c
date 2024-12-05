/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:59:11 by atamas            #+#    #+#             */
/*   Updated: 2024/12/05 12:26:27 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_walls(t_ray *ray, t_struct *mlx, int x)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	if (ray->side == 0)
		ray->wall_x = mlx->player_y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = mlx->player_x + ray->wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex_x = (int)(ray->wall_x * (double)ray->t.width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = ray->t.width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = ray->t.width - tex_x - 1;
	step = 1.0 * ray->t.height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_Y / 2 + ray->line_height / 2) * step;
	while (ray->draw_start < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		ray->p_color = my_mlx_pixel_get(&ray->t, tex_x, tex_y);
		my_mlx_pixel_put(mlx, x, ray->draw_start, ray->p_color);
		ray->draw_start++;
	}
}

void	ray_calc(t_ray *ray, t_struct *mlx, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_X - 1;
	ray->ray_dir_x = mlx->dir_x + mlx->plane_x * ray->camera_x;
	ray->ray_dir_y = mlx->dir_y + mlx->plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player_x;
	ray->map_y = (int)mlx->player_y;
	ray->deltadist_x = fabs(1 / ray->ray_dir_x);
	ray->deltadist_y = fabs(1 / ray->ray_dir_y);
}

void	pre_dda(t_ray *ray, t_struct *mlx)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (mlx->player_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - mlx->player_x)
			* ray->deltadist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (mlx->player_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - mlx->player_y)
			* ray->deltadist_y;
	}
}

void	dda(t_ray *ray, t_struct *mlx)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (mlx->parse->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->deltadist_y);
}

void	ray_cast(t_struct *mlx)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_X)
	{
		ray_calc(&ray, mlx, x);
		pre_dda(&ray, mlx);
		dda(&ray, mlx);
		line_height(&ray);
		choose_img_side(&ray, mlx);
		put_walls(&ray, mlx, x);
		x++;
	}
}
