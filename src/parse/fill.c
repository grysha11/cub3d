/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:17:23 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/06 11:25:27 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	neighbour(char **map, t_point size, t_point start)
{
	int		i;
	t_point	c[4];

	c[0] = (t_point){start.x, start.y - 1};
	c[1] = (t_point){start.x, start.y + 1};
	c[2] = (t_point){start.x - 1, start.y};
	c[3] = (t_point){start.x + 1, start.y};
	if (!check_for_null(c, map))
		return (false);
	i = 0;
	while (i < 4)
	{
		if (c[i].y >= 0 && c[i].x >= 0 && c[i].y < size.y && c[i].x < size.x)
		{
			if (map[c[i].y][c[i].x] == ' ' || map[c[i].y][c[i].x] == '\0')
				return (false);
			i++;
		}
	}
	return (true);
}

bool	fill(char **map, t_point size, t_point start)
{
	char	c;

	if (start.y < 0 || start.y >= size.y || start.x < 0 || start.x >= size.x)
		return (true);
	c = map[start.y][start.x];
	if (c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		if (start.y >= size.y - 1 || start.y == 0
			|| start.x == 0 || start.x >= size.x - 1)
			return (false);
		if (!neighbour(map, size, start))
			return (false);
		map[start.y][start.x] = 'X';
		if (!fill(map, size, (t_point){start.x, start.y - 1}) ||
		!fill(map, size, (t_point){start.x, start.y + 1}) ||
		!fill(map, size, (t_point){start.x - 1, start.y}) ||
		!fill(map, size, (t_point){start.x + 1, start.y}))
			return (false);
	}
	return (true);
}

bool	fill_loop(t_flood *flood)
{
	int	i;

	i = 0;
	while (flood->s_cord[i].x != -1)
	{
		if (!fill(flood->map, flood->size, flood->s_cord[i]))
			return (false);
		i++;
	}
	return (true);
}

void	init_flood(t_parse *parse)
{
	t_flood	flood;

	flood.map = cpy_matrix(parse->map);
	get_w_h(&flood, parse);
	get_cords(&flood, get_n_cords(parse->map), parse->map);
	if (!fill_loop(&flood))
	{
		free(flood.s_cord);
		free_matrixx(flood.map);
		free_parse(parse);
		err_inc_parse("Map is not closed");
		exit(1);
	}
	free(flood.s_cord);
	free_matrixx(flood.map);
}
