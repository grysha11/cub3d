/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:14 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/30 23:25:34 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	take_texture(char **str, t_parse *parse)
{
	if (ft_strncmp(str[0], "NO", ft_strlen(str[0])) == 0)
	{
		parse->textures[NO] = ft_strdup(str[1]);
		parse->no++;
	}
	else if (ft_strncmp(str[0], "SO", ft_strlen(str[0])) == 0)
	{
		parse->textures[SO] = ft_strdup(str[1]);
		parse->so++;
	}
	else if (ft_strncmp(str[0], "WE", ft_strlen(str[0])) == 0)
	{
		parse->textures[WE] = ft_strdup(str[1]);
		parse->we++;
	}
	else if (ft_strncmp(str[0], "EA", ft_strlen(str[0])) == 0)
	{
		parse->textures[EA] = ft_strdup(str[1]);
		parse->ea++;
	}
	else
		return ;
}

void	valid_textures(t_parse *parse)
{
	if (parse->no != 1 || parse->so != 1 || parse->we != 1 || parse->ea != 1)
	{
		err_inc_parse("Incorect amount of textures");
		free_parse(parse);
		exit(1);
	}
}

void	parse_textures(t_parse *parse)
{
	int		i;
	int		count;
	char	**res;

	count = 0;
	while (count < 4)
	{
		i = find_str(parse->map);
		res = ft_split(parse->map[i], ' ');
		if (matrix_len(res) != 2)
		{
			err_inc_parse("Incorrect amount of textures");
			free_matrixx(res);
			free_parse(parse);
			exit(1);
		}
		take_texture(res, parse);
		free_matrixx(res);
		count++;
	}
	valid_textures(parse);
}
