/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/17 19:15:59 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_inc_parse(char *first_message)
{
	printf("%sERROR %s: %s\n\t", COLOR_RED, first_message, COLOR);
	printf("Try: %s./cub3d map.cub%s\n", COLOR_CYAN, COLOR);
}

void	check_files(char **av, int ac, t_parse *parse)
{
	char	*ext;

	if (ac != 2)
	{
		err_inc_parse("Incorrect amount of arguments");
		free_parse(parse);
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
		free_parse(parse);
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
		free_parse(parse);
		exit(1);
	}
	parse->map = ft_get_file(fd, 0);
	if (!parse->map)
	{
		close(fd);
		err_inc_parse("Could't read the .cub file");
		free_parse(parse);
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

int	create_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	take_colors(char **str, t_parse *parse)
{
	char	**res;
	int		color[3];

	if (ft_strncmp(str[0], "C", ft_strlen(str[0])) == 0)
	{
		
		res = ft_split(str[1], ',');
		color[0] = ft_atoi(res[0]);
		color[1] = ft_atoi(res[1]);
		color[2] = ft_atoi(res[2]);
		parse->c_color = create_rgb(color);
		free_matrixx(res);
	}
	else if (ft_strncmp(str[0], "F", ft_strlen(str[0])) == 0)
	{
		res = ft_split(str[1], ',');
		color[0] = ft_atoi(res[0]);
		color[1] = ft_atoi(res[1]);
		color[2] = ft_atoi(res[2]);
		parse->f_color = create_rgb(color);
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

int	find_map(t_parse *parse)
{
	int	i;

	i = 0;
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
		i++;
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) == 0)
		i++;
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
		i++;
	return (i + 1);
}

void	find_player(t_parse *parse)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	i = find_map(parse);
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] != '0' && parse->map[i][j] != '1')
			{
				parse->dir = parse->map[i][j];
				parse->x = (double)j;
				parse->y = (double)y;
			}
			j++;
		}
		y++;
		i++;
	}
}

int		matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	trim_map(t_parse *parse)
{
	char	**res;
	int		len;
	int		i;

	len = find_map(parse);
	res = malloc(sizeof(char *) * (matrix_len(parse->map + len) + 1));
	i = 0;
	while (ft_strncmp(parse->map[len], "\n", ft_strlen(parse->map[len])) != 0 &&
			parse->map[len] != NULL)
	{
		res[i] = ft_strdup(parse->map[len]);
		len++;
		i++;
	}
	res[i] = NULL;
	res[(int)parse->x][(int)parse->y] = '0';
	free_matrixx(parse->map);
	parse->map = res;
}
