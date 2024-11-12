/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:37 by atamas            #+#    #+#             */
/*   Updated: 2024/11/12 16:35:30 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./minilibx/mlx.h"

// int	main(void)
// {
// 	t_struct	mlx;

// 	set_up_player(&mlx);
// 	if (mlx_setup(&mlx))
// 		return (1);
// 	draw_triangle(25, mlx.player_x, mlx.player_y, RED, &mlx);
// 	// draw_square(50, mlx.player_x, mlx.player_y, RED, &mlx);
// 	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
// 	mlx_loop(mlx.mlx);
// 	clean_exit(&mlx);
// 	return (0);
// }

void	init_parse(int ac, char **av, t_parse *parse)
{
	check_files(av, ac);
	parse_file(av, parse);
	if (!check_order(parse->map))
	{
		free_parse(parse);
		err_inc_parse("Incorrect order of instructions");
		exit(1);
	}
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


int	main(int ac, char **av)
{
	t_parse	*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	init_parse(ac, av, parse);
	print_parse(parse);
	free_parse(parse);
	return (0);
}
