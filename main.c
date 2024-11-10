/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:37 by atamas            #+#    #+#             */
/*   Updated: 2024/11/10 17:33:11 by hzakharc         ###   ########.fr       */
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


int	main(int ac, char **av)
{
	t_parse	*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	check_files(av, ac);
	parse_file(av, parse);
	parse_textures(parse);
	parse_colors(parse);
	find_player(parse);
	trim_map(parse);
	for (int i = 0; parse->map[i]; i++)
		printf("%s\n", parse->map[i]);
	// for (int i = 0; parse->textures[i]; i++)
	// 	printf("%s\n", parse->textures[i]);
	// for (int i = 0; i < 3; i++)
	// 	printf("%d\n", parse->f_color[i]);
	// printf("\n");
	// for (int i = 0; i < 3; i++)
	// 	printf("%d\n", parse->c_color[i]);
	for (int i = 0; parse->map[i]; i++)
		free(parse->map[i]);
	for (int i = 0; parse->textures[i]; i++)
		free(parse->textures[i]);
	free(parse->map);
	free(parse);
	return (0);
}
