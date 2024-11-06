/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:37 by atamas            #+#    #+#             */
/*   Updated: 2024/11/06 12:54:40 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./minilibx/mlx.h"

int	main(void)
{
	t_struct	mlx;

	set_up_player(&mlx);
	if (mlx_setup(&mlx))
		return (1);
	draw_triangle(25, mlx.player_x, mlx.player_y, RED, &mlx);
	// draw_square(50, mlx.player_x, mlx.player_y, RED, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	return (0);
}
