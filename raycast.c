/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:59:11 by atamas            #+#    #+#             */
/*   Updated: 2024/11/23 00:05:31 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_texture_color(t_ray *ray, t_struct *mlx, int x)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	if (ray->side == 0)
		wall_x = mlx->player_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = mlx->player_x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)mlx->n_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = mlx->n_width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = mlx->n_width - tex_x - 1;
	step = 1.0 * mlx->n_height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_Y / 2 + ray->line_height / 2) * step;
	while (ray->draw_start < ray->draw_end)
	{
		tex_y = (int)tex_pos & (mlx->n_height - 1);
		tex_pos += step;
		color = *(unsigned int *)(mlx->n_addr + mlx->n_line_length * tex_y + tex_x * (mlx->n_b_p_p / 8));
		my_mlx_pixel_put(mlx, x, ray->draw_start, color);
		ray->draw_start++;
	}
	return color;
}

int		choose_img_side(t_ray *ray)
{
	int	img;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			img = RED; // left aka west side
		else
			img = 0x0000FF; // right aka east side
	}
	else
	{
		if (ray->ray_dir_y < 0)
			img = 0x00FFFFFF; // north side
		else
			img = 0x0000FF00; // south side
	}
	return (img);
}

void	draw_vline(t_ray *ray, t_struct *mlx, int x)
{
	// int	t;
	// int	img;

	// t = ray->draw_start;
	// img = choose_img_side(ray);
	// // color & 8355711
	find_texture_color(ray, mlx, x);
	// while (t < ray->draw_end)
	// {
	// 	my_mlx_pixel_put(mlx, x, t, img);
	// 	t++;
	// }
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
}

void	ray_cast(t_struct *mlx)
{
	t_ray	ray;
	int		x;

	x = 0;
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