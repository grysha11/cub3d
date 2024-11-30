/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:24:25 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/30 23:23:59 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int *rgb, t_parse *parse)
{
	if ((rgb[0] >= 0 && rgb[0] <= 255) && (rgb[1] >= 0 && rgb[1] <= 255)
		&& (rgb[2] >= 0 && rgb[2] <= 255))
		return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	else
	{
		err_inc_parse("Incorrect color values");
		free_parse(parse);
		exit(1);
	}
}

void	check_colors(char **str, t_parse *parse, int *dst)
{
	char	**res;
	int		colors[3];

	res = ft_split(str[1], ',');
	if (matrix_len(res) != 3)
	{
		err_inc_parse("Incorrect amount of RGB values");
		free_matrixx(res);
		free_matrixx(str);
		free_parse(parse);
		exit(1);
	}
	colors[0] = ft_atoi(res[0]);
	colors[1] = ft_atoi(res[1]);
	colors[2] = ft_atoi(res[2]);
	free_matrixx(res);
	*dst = create_rgb(colors, parse);
}

void	take_colors(char **str, t_parse *parse)
{
	if (ft_strncmp(str[0], "C", ft_strlen(str[0])) == 0)
	{
		parse->c++;
		check_colors(str, parse, &parse->c_color);
	}
	else if (ft_strncmp(str[0], "F", ft_strlen(str[0])) == 0)
	{
		parse->f++;
		check_colors(str, parse, &parse->f_color);
	}
	else
		return ;
}

void	parse_colors(t_parse *parse)
{
	int		i;
	int		count;
	char	**res;

	count = 0;
	while (count < 2)
	{
		i = find_str(parse->map);
		res = ft_split(parse->map[i], ' ');
		if (matrix_len(res) != 2)
		{
			err_inc_parse("Incorrect format of colors");
			free_matrixx(res);
			free_parse(parse);
			exit(1);
		}
		take_colors(res, parse);
		free_matrixx(res);
		count++;
	}
}
