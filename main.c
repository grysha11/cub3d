/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:37 by atamas            #+#    #+#             */
/*   Updated: 2024/11/05 13:23:57 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./minilibx/mlx.h"

int	main(void)
{
	t_struct	mlx;

	mlx.player_x = SCREEN_X / 2;
	mlx.player_y = SCREEN_Y / 2;
	mlx.dir_x = 0;
	mlx.dir_y = -1;
	mlx.plane_x = 0.66;
	mlx.plane_y = 0;
	mlx.move_speed = 5;
	mlx.rotate_speed = 3;
	// set which box in the map are we in
	if (mlx_setup(&mlx))
		return (1);
	draw_triangle(25, mlx.player_x, mlx.player_y, RED, &mlx);
	// draw_square(50, mlx.player_x, mlx.player_y, RED, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	return (0);
}
