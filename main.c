/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:37 by atamas            #+#    #+#             */
/*   Updated: 2024/11/23 00:17:24 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./minilibx/mlx.h"

void	init_parse(int ac, char **av, t_parse *parse)
{
	check_files(av, ac, parse);
	parse_file(av, parse);
	parse_textures(parse);
	parse_colors(parse);
	find_player(parse);
	trim_map(parse);
}

void	free_parse(t_parse *parse)
{
	int	i;

	if (parse)
	{
		if (parse->map)
		{
			i = 0;
			while (parse->map[i] != NULL)
			{
				free(parse->map[i]);
				i++;
			}
			free(parse->map);
		}
		i = 0;
		while (parse->textures[i])
		{
			free(parse->textures[i]);
			i++;
		}
	}
	free(parse);
}

void	print_parse(t_parse *parse)
{
	printf("MAP: \n");
	for (int i = 0; parse->map[i]; i++)
		printf("%s\n", parse->map[i]);
	printf("TEXTURE PATHES: \n");
	for (int i = 0; parse->textures[i]; i++)
		printf("%s\n", parse->textures[i]);
	printf("FLOOR COLOR: \n%d\n", parse->f_color);
	printf("CEELING COLOR: \n%d\n", parse->c_color);
}

unsigned int my_mlx_pixel_get(t_struct *data, int x, int y)
{
    char	*src;

    src = data->addr + (y * data->line_length + x * (data->b_p_p / 8));
    return *(unsigned int *)src;
}

void	init_texture(t_struct *mlx)
{

	mlx->north_img = mlx_xpm_file_to_image(mlx->mlx, "./inc/north.xpm", &mlx->n_width, &mlx->n_height);
	mlx->n_addr = mlx_get_data_addr(mlx->north_img, &mlx->n_b_p_p, &mlx->n_line_length, &mlx->n_endian);
	mlx->south_img = mlx_xpm_file_to_image(mlx->mlx, "./inc/south.xpm", &mlx->s_width, &mlx->s_height);
	mlx->s_addr = mlx_get_data_addr(mlx->south_img, &mlx->s_b_p_p, &mlx->s_line_length, &mlx->s_endian);
	mlx->east_img = mlx_xpm_file_to_image(mlx->mlx, "./inc/east.xpm", &mlx->e_width, &mlx->e_height);
	mlx->e_addr = mlx_get_data_addr(mlx->east_img, &mlx->e_b_p_p, &mlx->e_line_length, &mlx->e_endian);
	mlx->west_img = mlx_xpm_file_to_image(mlx->mlx, "./inc/west.xpm", &mlx->w_width, &mlx->w_height);
	mlx->w_addr = mlx_get_data_addr(mlx->west_img, &mlx->w_b_p_p, &mlx->w_line_length, &mlx->w_endian);
}

int	main(int ac, char **av)
{
	t_struct	mlx;
	t_parse	*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	mlx.parse = parse;
	init_parse(ac, av, parse);
	set_up_player(&mlx);
	print_parse(parse);
	if (mlx_setup(&mlx))
		return (1);
	init_texture(&mlx);
	// print_parse(parse);
	// draw_map(&mlx);
	clear_screen(&mlx);
	ray_cast(&mlx);
	// draw_square(5, (mlx.player_x + 1) * BLOCK_SIZE, (mlx.player_y + 1) * BLOCK_SIZE, RED, &mlx);
	// draw_triangle(32, (mlx.player_x + 1) * 32, (mlx.player_y + 1) * 32, RED, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	return (0);
}
