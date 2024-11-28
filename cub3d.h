/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:30:34 by atamas            #+#    #+#             */
/*   Updated: 2024/11/28 17:19:46 by atamas           ###   ########.fr       */
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
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.5

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

typedef struct s_textures
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		b_p_p;
	int		line_length;
	int		endian;
}	t_textures;

typedef struct s_keys
{
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	r_right;
	bool	r_left;
}	t_keys;

typedef struct s_struct
{
	void		*mlx;
	void		*mlx_win;
	t_parse		*parse;
	t_textures	texture[4];
	t_keys		key;
	void		*img;
	char		*addr;
	int			b_p_p;
	int			line_length;
	int			endian;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		player_orient;
	int			prev_x;
	double		move_speed;
	double		rotate_speed;
}	t_struct;

typedef struct s_ray
{
	t_struct	*mlx;
	t_textures	t;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		deltadist_x;
	double		deltadist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side;
	double		wall_x;
	int			p_color;
}	t_ray;

void			my_mlx_pixel_put(t_struct *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_textures *data, int x, int y);
void			clear_screen(t_struct *mlx);
void			draw_map(t_struct *mlx);
void			rotate(t_struct *mlx);
void			movement(t_struct *mlx);
int				mlx_setup(t_struct *mlx);
void			set_up_player(t_struct *mlx);
int				clean_exit(t_struct *mlx);
void			ray_cast(t_struct *mlx);
void			line_height(t_ray *ray);
void			choose_img_side(t_ray *ray, t_struct *mlx);
int				render(t_struct *mlx);

//parsing functions
void			parse_file(char **av, t_parse *parse);
void			check_files(char **av, int ac, t_parse *parse);
void			err_inc_parse(char *first_message);
void			parse_textures(t_parse *parse);
void			parse_colors(t_parse *parse);
int				find_map(t_parse *parse);
void			find_player(t_parse *parse);
void			trim_map(t_parse *parse);
void			free_parse(t_parse *parse);

#endif
