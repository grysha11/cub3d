/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:26:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/30 23:28:13 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_parse *parse)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	i = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] != '0' &&
				parse->map[i][j] != '1' && parse->map[i][j] != ' ')
			{
				parse->dir = parse->map[i][j];
				parse->map[i][j] = '0';
				parse->x = (double)j;
				parse->y = (double)y;
			}
			j++;
		}
		y++;
		i++;
	}
}

void	trim_map(t_parse *parse)
{
	char	**res;
	int		len;
	int		i;

	len = find_str(parse->map);
	res = malloc(sizeof(char *) * (matrix_len(parse->map + len) + 1));
	i = 0;
	while (parse->map[len] && ft_strncmp(parse->map[len],
			"\n", ft_strlen(parse->map[len])) != 0)
	{
		res[i] = ft_strdup(parse->map[len]);
		len++;
		i++;
	}
	res[i] = NULL;
	free_matrixx(parse->map);
	parse->map = res;
}

void	get_w_h(t_flood *flood, t_parse *parse)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	w = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
			j++;
		if (j > w)
			w = j;
		i++;
	}
	flood->size.x = w + 1;
	flood->size.y = i;
}

int	get_n_cords(char **map)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
				res++;
			j++;
		}
		i++;
	}
	return (res);
}

void	get_cords(t_flood *flood, int size, char **map)
{
	int	i;
	int	j;
	int	c;

	flood->s_cord = malloc(sizeof(t_point) * (size + 1));
	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
			{
				flood->s_cord[c].x = j;
				flood->s_cord[c].y = i;
				c++;
			}
			j++;
		}
		i++;
	}
	flood->s_cord[c].x = -1;
	flood->s_cord[c].y = -1;
}
