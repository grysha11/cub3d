/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:44:24 by atamas            #+#    #+#             */
/*   Updated: 2024/11/28 17:20:39 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_struct *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->b_p_p / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_textures *data, int x, int y)
{
	char	*src;

	src = data->addr + (y * data->line_length + x * (data->b_p_p / 8));
	return (*(unsigned int *)src);
}

void	clear_screen(t_struct *mlx)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	color = mlx->parse->c_color;
	while (i < SCREEN_Y)
	{
		j = 0;
		if (i > SCREEN_Y / 2)
			color = mlx->parse->f_color;
		while (j < SCREEN_X)
		{
			j++;
			my_mlx_pixel_put(mlx, j, i, color);
		}
		i++;
	}
}

// void	draw_square(int size, int x, int y, int color, t_struct *game)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 		my_mlx_pixel_put(game, x + i++, y, color);
// 	i = 0;
// 	while (i < size)
// 		my_mlx_pixel_put(game, x, y + i++, color);
// 	i = 0;
// 	while (i < size)
// 		my_mlx_pixel_put(game, x + size, y + i++, color);
// 	i = 0;
// 	while (i < size)
// 		my_mlx_pixel_put(game, x + i++, y + size, color);
// }

// void	draw_map(t_struct *mlx)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (mlx->parse->map[y])
// 	{
// 		x = 0;
// 		while (mlx->parse->map[y][x])
// 		{
// 			if (mlx->parse->map[y][x] == '1')
// 				draw_square(32, (x + 1) * BLOCK_SIZE, (y + 1) * BLOCK_SIZE,
// 					RED, mlx);
// 			x++;
// 		}
// 		y++;
// 	}
// }
