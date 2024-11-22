/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:34 by atamas            #+#    #+#             */
/*   Updated: 2024/11/22 23:56:32 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include "./minilibx/mlx.h"
# include "inc/gnl/gnl.h"
# include "inc/libft/libft.h"

# define SCREEN_X 1024
# define SCREEN_Y 720
# define TEXTURE_X 64
# define TEXTURE_Y 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define BLOCK_SIZE 32
# define PI 3.141592
# define RED 0x00FF0000

# define COLOR "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

typedef enum e_texture
{
	NO,
	SO,
	WE,
	EA
}	t_texture;

typedef struct s_parse
{
	char	**map;
	char	dir;
	double	x;
	double	y;
	char	*textures[10];
	int		c_color;
	int		f_color;
}	t_parse;

typedef struct s_struct
{
	void	*mlx;
	void	*mlx_win;
	t_parse	*parse;
	void	*north_img;
	int		n_width;
	int		n_height;
	char	*n_addr;
	int		n_b_p_p;
	int		n_line_length;
	int		n_endian;
	void	*south_img;
	int		s_width;
	int		s_height;
	char	*s_addr;
	int		s_b_p_p;
	int		s_line_length;
	int		s_endian;
	void	*west_img;
	int		w_width;
	int		w_height;
	char	*w_addr;
	int		w_b_p_p;
	int		w_line_length;
	int		w_endian;
	void	*east_img;
	int		e_width;
	int		e_height;
	char	*e_addr;
	int		e_b_p_p;
	int		e_line_length;
	int		e_endian;
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
	int		prev_x;
	double	move_speed;
	double	rotate_speed;
}	t_struct;


typedef struct s_ray
{
	t_struct	*mlx;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		side;
}	t_ray;

void	my_mlx_pixel_put(t_struct *data, int x, int y, int color);
void	clear_screen(t_struct *mlx);
void	draw_square(int size, int x, int y, int color, t_struct *game);
// void	draw_triangle(int size, int x, int y, int color, t_struct *mlx);
void	draw_map(t_struct *mlx);
void	rotate(int keycode, t_struct *mlx);
void	movement(int keycode, t_struct *mlx);
int		mlx_setup(t_struct *mlx);
void	set_up_player(t_struct *mlx);
int		clean_exit(t_struct *mlx);
void	ray_cast(t_struct *mlx);

//parsing functions
void	parse_file(char **av, t_parse *parse);
void	check_files(char **av, int ac, t_parse *parse);
void	err_inc_parse(char *first_message);
void	parse_textures(t_parse *parse);
void	parse_colors(t_parse *parse);
int		find_map(t_parse *parse);
void	find_player(t_parse *parse);
void	trim_map(t_parse *parse);
void	free_parse(t_parse *parse);

#endif
