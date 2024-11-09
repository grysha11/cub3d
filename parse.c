/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/09 18:26:44 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_inc_parse(char *first_message)
{
	printf("%sERROR %s: %s\n\t", COLOR_RED, first_message, COLOR);
	printf("Try: %s./cub3d map.cub%s\n", COLOR_CYAN, COLOR);
}

void	check_files(char **av, int ac)
{
	char	*ext;

	if (ac != 2)
	{
		err_inc_parse("Incorrect amount of arguments");
		exit(1);
	}
	ext = ft_strdup(".cub");
	if (ft_strlen(av[1]) >= 4 && ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ext, 4) == 0)
	{
		free(ext);
		return ;
	}
	else
	{
		free(ext);
		err_inc_parse("Incorrect extension of the file");
		exit(1);
	}
}

void	parse_file(char **av, t_parse *parse)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		err_inc_parse("Could't open the .cub file");
		exit(1);
	}
	parse->map = ft_get_file(fd, 0);
	if (!parse->map)
	{
		close(fd);
		err_inc_parse("Could't read the .cub file");
		exit(1);
	}
	close(fd);
}

void	take_texture(char **str, t_parse *parse)
{
	if (ft_strncmp(str[0], "NO", ft_strlen(str[0])) == 0)
		parse->textures[NO] = ft_strdup(str[1]);
	else if (ft_strncmp(str[0], "SO", ft_strlen(str[0])) == 0)
		parse->textures[SO] = ft_strdup(str[1]);
	else if (ft_strncmp(str[0], "WE", ft_strlen(str[0])) == 0)
		parse->textures[WE] = ft_strdup(str[1]);
	else if (ft_strncmp(str[0], "EA", ft_strlen(str[0])) == 0)
		parse->textures[EA] = ft_strdup(str[1]);
	else
		return ;
}

void	free_matrixx(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	parse_textures(t_parse *parse)
{
	int		i;
	int		j;
	char	delim;
	char	**res;

	i = 0; 
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] == ' ')
				delim = ' ';
			else if (parse->map[i][j] == '\t')
				delim = '\t';
			j++;
		}
		res = ft_split(parse->map[i], delim);
		take_texture(res, parse);
		free_matrixx(res);
		i++;
	}
}

void	take_colors(char **str, t_parse *parse)
{
	char	**res;

	if (ft_strncmp(str[0], "C", ft_strlen(str[0])) == 0)
	{
		
		res = ft_split(str[1], ',');
		parse->c_color[0] = ft_atoi(res[0]);
		parse->c_color[1] = ft_atoi(res[1]);
		parse->c_color[2] = ft_atoi(res[2]);
		free_matrixx(res);
	}
	else if (ft_strncmp(str[0], "F", ft_strlen(str[0])) == 0)
	{
		res = ft_split(str[1], ',');
		parse->f_color[0] = ft_atoi(res[0]);
		parse->f_color[1] = ft_atoi(res[1]);
		parse->f_color[2] = ft_atoi(res[2]);
		free_matrixx(res);
	}
	else
		return ;
}

void	parse_colors(t_parse *parse)
{
	int		i;
	char	**res;

	i = 0;
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
		i++;
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) == 0)
		i++;
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
	{
		res = ft_split(parse->map[i], ' ');
		take_colors(res, parse);
		free_matrixx(res);
		i++;
	}
}
