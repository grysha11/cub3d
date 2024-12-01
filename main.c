/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:37 by atamas            #+#    #+#             */
/*   Updated: 2024/12/01 22:33:55 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./minilibx/mlx.h"

void	init_parse(int ac, char **av, t_parse *parse)
{
	check_files(av, ac);
	parse_file(av, parse);
	tab_trim(parse);
	parse_textures(parse);
	parse_colors(parse);
	if (parse->c != 1 || parse->f != 1)
	{
		err_inc_parse("Incorrect amount of colors");
		free_parse(parse);
		exit(1);
	}
	trim_map(parse);
	check_map_chars(parse);
	find_player(parse);
	init_flood(parse);
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

void	set_textures(t_struct *mlx, char **textures)
{
	mlx->texture[NO].img = mlx_xpm_file_to_image(mlx->mlx, textures[NO],
			&mlx->texture[NO].width, &mlx->texture[NO].height);
	mlx->texture[SO].img = mlx_xpm_file_to_image(mlx->mlx, textures[SO],
			&mlx->texture[SO].width, &mlx->texture[SO].height);
	mlx->texture[WE].img = mlx_xpm_file_to_image(mlx->mlx, textures[WE],
			&mlx->texture[WE].width, &mlx->texture[WE].height);
	mlx->texture[EA].img = mlx_xpm_file_to_image(mlx->mlx, textures[EA],
			&mlx->texture[EA].width, &mlx->texture[EA].height);
	if (mlx->texture[NO].img == NULL || mlx->texture[SO].img == NULL
		|| mlx->texture[WE].img == NULL || mlx->texture[EA].img == NULL)
		return (printf("Error\nOne of the IMG returned NULL\n"),
			clean_exit(mlx), exit(1));
	mlx->texture[NO].addr = mlx_get_data_addr(mlx->texture[NO].img,
			&mlx->texture[NO].b_p_p, &mlx->texture[NO].line_length,
			&mlx->texture[NO].endian);
	mlx->texture[SO].addr = mlx_get_data_addr(mlx->texture[SO].img,
			&mlx->texture[SO].b_p_p, &mlx->texture[SO].line_length,
			&mlx->texture[SO].endian);
	mlx->texture[WE].addr = mlx_get_data_addr(mlx->texture[WE].img,
			&mlx->texture[WE].b_p_p, &mlx->texture[WE].line_length,
			&mlx->texture[WE].endian);
	mlx->texture[EA].addr = mlx_get_data_addr(mlx->texture[EA].img,
			&mlx->texture[EA].b_p_p, &mlx->texture[EA].line_length,
			&mlx->texture[EA].endian);
}

int	main(int ac, char **av)
{
	t_struct	mlx;
	t_parse		*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	mlx.parse = parse;
	init_parse(ac, av, parse);
	set_up_player(&mlx);
	if (mlx_setup(&mlx))
		return (1);
	set_textures(&mlx, parse->textures);
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_loop(mlx.mlx);
	clean_exit(&mlx);
	free_parse(parse);
	return (0);
}
