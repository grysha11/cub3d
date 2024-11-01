/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:34 by atamas            #+#    #+#             */
/*   Updated: 2024/11/01 15:12:11 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_X 3840 / 2
# define SCREEN_Y 2160 / 2
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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	deltadist_x;
	double	deltadist_y;
	double	perpWall;
	double	move_speed;
	double	rotate_speed;
	int		hit;
	int		side;
}	t_struct;

#endif