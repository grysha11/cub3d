/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:34 by atamas            #+#    #+#             */
/*   Updated: 2024/11/06 12:48:18 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# define SCREEN_X 1024
# define SCREEN_Y 720
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define PI 3.141592
# define RED 0x00FF0000

typedef struct s_struct
{
	void	*mlx;
	void	*mlx_win;

	void	*img;
	char	*addr;
	int		b_p_p;
	int		line_length;
	int		endian;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	player_orient;
	//
	double	camera_x;
	double	deltadist_x;
	double	deltadist_y;
	double	perpWall;
	double	move_speed;
	double	rotate_speed;
	int		hit;
	int		side;
}	t_struct;

void	my_mlx_pixel_put(t_struct *data, int x, int y, int color);
void	clear_screen(t_struct *mlx);
void	draw_square(int size, int x, int y, int color, t_struct *game);
void	draw_triangle(int size, int x, int y, int color, t_struct *mlx);
void	rotate(int keycode, t_struct *mlx);
void	movement(int keycode, t_struct *mlx);
int		mlx_setup(t_struct *mlx);
void	set_up_player(t_struct *mlx);
int		clean_exit(t_struct *mlx);
#endif
