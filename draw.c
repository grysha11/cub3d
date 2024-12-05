/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:44:24 by atamas            #+#    #+#             */
/*   Updated: 2024/12/05 12:32:48 by atamas           ###   ########.fr       */
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
