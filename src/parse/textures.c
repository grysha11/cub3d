/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:14 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/06 11:25:40 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_extension_t(t_parse *parse, char **str, int i)
{
	char	*ext;

	ext = ft_strdup(".xpm");
	if (ft_strlen(str[1]) >= 4 && ft_strncmp(str[1]
			+ ft_strlen(str[1]) - 4, ext, 4) != 0)
	{
		err_inc_parse("Incorrect extension of the texture file");
		free(ext);
		free_matrixx(str);
		free_parse(parse);
		exit(1);
	}
	else
	{
		parse->textures[i] = ft_strdup(str[1]);
	}
	free(ext);
}

void	take_texture(char **str, t_parse *parse)
{
	if (ft_strncmp(str[0], "NO", ft_strlen(str[0])) == 0)
	{
		check_extension_t(parse, str, NO);
		parse->no++;
	}
	else if (ft_strncmp(str[0], "SO", ft_strlen(str[0])) == 0)
	{
		check_extension_t(parse, str, SO);
		parse->so++;
	}
	else if (ft_strncmp(str[0], "WE", ft_strlen(str[0])) == 0)
	{
		check_extension_t(parse, str, WE);
		parse->we++;
	}
	else if (ft_strncmp(str[0], "EA", ft_strlen(str[0])) == 0)
	{
		check_extension_t(parse, str, EA);
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
