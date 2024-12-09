/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:02:15 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/06 11:24:55 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_count(t_parse *parse)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] == 'N' || parse->map[i][j] == 'S' ||
				parse->map[i][j] == 'W' || parse->map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		err_inc_parse("Incorrect amount of players in map");
		free_parse(parse);
		exit(1);
	}
}

void	check_map_chars(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] != '0' && parse->map[i][j] != '1' &&
				parse->map[i][j] != 'N' && parse->map[i][j] != 'S' &&
				parse->map[i][j] != 'W' && parse->map[i][j] != 'E' &&
				parse->map[i][j] != ' ')
			{
				err_inc_parse("Unknown character in the map");
				free_parse(parse);
				exit(1);
			}
			j++;
		}
		i++;
	}
	check_count(parse);
}

bool	check_for_null(t_point *c, char **map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (c[i].x >= (int)ft_strlen(map[c[i].y]) || c[i].y >= matrix_len(map))
			return (false);
		i++;
	}
	return (true);
}
