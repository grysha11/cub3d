/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:44:24 by atamas            #+#    #+#             */
/*   Updated: 2024/11/05 12:46:00 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_screen(t_struct *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SCREEN_Y)
	{
		j = 0;
		while (j < SCREEN_X)
		{
			j++;
			my_mlx_pixel_put(mlx, j, i, 0);
		}
		i++;
	}
}

void	draw_square(int size, int x, int y, int color, t_struct *game)
{
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x + i, y, color);
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x, y + i, color);
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x + size, y + i, color);
	for(int i = 0; i < size; i++)
		my_mlx_pixel_put(game, x + i, y + size, color);
}

void	draw_line(t_struct *mlx, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		if (x0 >= 0 && x0 < SCREEN_X && y0 >= 0 && y0 < SCREEN_Y)
			my_mlx_pixel_put(mlx, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_triangle(int size, int x, int y, int color, t_struct *mlx)
{
	double	angle = atan2(mlx->dir_y, mlx->dir_x);
	double	half_base = size / 2.0;
	double	height = size * 1.5;

	// Calculate the vertices of the triangle
	int v1_x = x + height * cos(angle);
	int v1_y = y + height * sin(angle);
	int v2_x = x - half_base * cos(angle + PI / 2);
	int v2_y = y - half_base * sin(angle + PI / 2);
	int v3_x = x + half_base * cos(angle + PI / 2);
	int v3_y = y + half_base * sin(angle + PI / 2);

	// Draw lines between the vertices
	draw_line(mlx, v1_x, v1_y, v2_x, v2_y, color);
	draw_line(mlx, v2_x, v2_y, v3_x, v3_y, color);
	draw_line(mlx, v3_x, v3_y, v1_x, v1_y, color);
}
