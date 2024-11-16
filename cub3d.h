/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:34 by atamas            #+#    #+#             */
/*   Updated: 2024/11/12 16:34:13 by hzakharc         ###   ########.fr       */
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
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
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

typedef struct s_flood
{
	int		x;
	int		y;
	int		rows;
	int		col;
	char	**map;
	char	**visited;
}	t_flood;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

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

//parsing functions
void	parse_file(char **av, t_parse *parse);
void	check_files(char **av, int ac);
bool	check_order(char **map);
void	err_inc_parse(char *first_message);
void	parse_textures(t_parse *parse);
void	parse_colors(t_parse *parse);
int		find_map(t_parse *parse);
void	find_player(t_parse *parse);
void	trim_map(t_parse *parse);
int		matrix_len(char **matrix);
void	free_parse(t_parse *parse);

#endif
