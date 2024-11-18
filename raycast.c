/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:59:11 by atamas            #+#    #+#             */
/*   Updated: 2024/11/18 17:42:10 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vline(t_ray *ray, t_struct *mlx, int x)
{
	int	t;
	int	color;

	t = ray->draw_start;
	color = RED;
	while (t < ray->draw_end)
	{
		if (ray->side == 1)
			color = 0x00ff00 / 2;
		my_mlx_pixel_put(mlx, x, t, color);
		t++;
	}
}

void	ray_calc(t_ray *ray, int x)
{
	t_struct	*mlx;

	mlx = ray->mlx;
	ray->camera_x = 2 * x / (double)SCREEN_X - 1;
	ray->ray_dir_x = mlx->dir_x + mlx->plane_x * ray->camera_x;
	ray->ray_dir_y = mlx->dir_y + mlx->plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player_x;
	ray->map_y = (int)mlx->player_y;
	ray->deltadist_x = fabs(1 / ray->ray_dir_x);
	ray->deltadist_y = fabs(1 / ray->ray_dir_y);
}

void	pre_dda(t_ray *ray)
{
	t_struct	*mlx;

	mlx = ray->mlx;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (mlx->player_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - mlx->player_x) * ray->deltadist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (mlx->player_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - mlx->player_y) * ray->deltadist_y;
	}
}

void	dda(t_ray *ray)
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
		if (ray->mlx->parse->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->deltadist_y);
}

void	line_height(t_ray *ray, int x)
{
	ray->line_height = (int)(SCREEN_Y / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + SCREEN_Y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_Y / 2;
	if (ray->draw_end >= SCREEN_Y)
		ray->draw_end = SCREEN_Y - 1;
	draw_vline(ray, ray->mlx, x);
	// mlx_put_image_to_window(ray->mlx->mlx, ray->mlx->mlx_win, ray->mlx->img, 0, 0);
}

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_dist = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	ray_cast(t_struct *mlx)
{
	t_ray	ray;
	int		x;

	x = 0;
	init_ray(&ray);
	ray.mlx = mlx;
	while (x < SCREEN_X)
	{
		ray_calc(&ray, x);
		pre_dda(&ray);
		dda(&ray);
		line_height(&ray, x);
		x++;
	}
}