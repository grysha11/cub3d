/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:15 by atamas            #+#    #+#             */
/*   Updated: 2024/10/28 09:34:28 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "./minilibx/mlx_int.h"
#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

int	clean_exit(t_struct *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int	event_handler(int keycode, t_struct *mlx)
{
	if (keycode == KEY_ESC)
		clean_exit(mlx);
	return (0);
}

int	mlx_setup(t_struct *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (write(2, "Failed to initalize mlx!\n", 25), 1);
	mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_X, SCREEN_Y, "Cub3D");
	if (!mlx->mlx_win)
		return (write(2, "Failed to create window!\n", 25), 1);
	mlx_hook(mlx->mlx_win, 17, 1L << 17, clean_exit, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, event_handler, mlx);
	return (0);
}

int	main(void)
{
	t_struct	mlx;

	if (mlx_setup(&mlx))
		return (1);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	return (0);
}
