/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:05:35 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/06 20:06:08 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	take_color_char(char *str, t_parse *parse)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 2 || (str[i] != 'C' && str[i] != 'F')
		|| str[i + 1] != ' ')
	{
		err_inc_parse("Incorrect format of color");
		free_parse(parse);
		exit(1);
	}
	return (str[i]);
}

void	validate_color(t_parse *parse, char **res)
{
	char	**check;
	int		i;

	i = 0;
	while (i < 3)
	{
		check = ft_split(res[i], ' ');
		if (matrix_len(check) > 1)
		{
			err_inc_parse("Incorrect format of colors");
			free_matrixx(res);
			free_matrixx(check);
			free_parse(parse);
			exit(1);
		}
		free_matrixx(check);
		i++;
	}
	check_numeric(parse, res);
}

void	format_color_helper(t_parse *parse, char **res, char color)
{
	int	c[3];

	validate_color(parse, res);
	c[0] = ft_atoi(res[0]);
	c[1] = ft_atoi(res[1]);
	c[2] = ft_atoi(res[2]);
	if (color == 'C')
	{
		parse->c_color = create_rgb(c, parse, res);
		parse->c++;
	}
	else if (color == 'F')
	{
		parse->f_color = create_rgb(c, parse, res);
		parse->f++;
	}
}

void	format_color(t_parse *parse, char *str)
{
	char	color;
	int		i;
	char	**res;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	color = take_color_char(str + i, parse);
	res = ft_split(str + i + 1, ',');
	if (matrix_len(res) == 3)
		format_color_helper(parse, res, color);
	else
	{
		err_inc_parse("Incorrect format of colors");
		free_matrixx(res);
		free_parse(parse);
		exit(1);
	}
	free_matrixx(res);
}

void	parse_colors(t_parse *parse)
{
	int	i;
	int	count;

	count = 0;
	while (count < 2)
	{
		i = find_str(parse->map);
		format_color(parse, parse->map[i]);
		count++;
	}
}
