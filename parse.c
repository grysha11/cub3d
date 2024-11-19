/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/19 15:13:59 by hzakharc         ###   ########.fr       */
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
	char	**res;

	i = 0; 
	while (ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
	{
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
		i++;
	}
}

int	create_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
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
	*dst = create_rgb(colors);
	free_matrixx(res);
}

void	take_colors(char **str, t_parse *parse)
{
	if (ft_strncmp(str[0], "C", ft_strlen(str[0])) == 0)
		check_colors(str, parse, &parse->c_color);
	else if (ft_strncmp(str[0], "F", ft_strlen(str[0])) == 0)
		check_colors(str, parse, &parse->f_color);
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
	while (parse->map[i] && ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
		i++;
	while (parse->map[i] && ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) == 0)
		i++;
	while (parse->map[i] && ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) != 0)
		i++;
	while (parse->map[i] && ft_strncmp(parse->map[i], "\n", ft_strlen(parse->map[i])) == 0)
		i++;
	return (i);
}

void	find_player(t_parse *parse)
{
	int	i;
	int	j;
	int	x;

	i = find_map(parse);
	x = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] != '0' && parse->map[i][j] != '1')
			{
				parse->dir = parse->map[i][j];
				parse->x = (double)x;
				parse->y = (double)j;
			}
			j++;
		}
		x++;
		i++;
	}
}

bool	check_order(char **map)
{
	int		i;
	bool	f_textures;
	bool	f_colors;

	i = 0;
	f_colors = false;
	f_textures = false;
	while (map[i])
	{
		if (ft_strncmp(map[i], "NO", 2) == 0 || ft_strncmp(map[i], "SO", 2) == 0 ||
			ft_strncmp(map[i], "WE", 2) == 0 || ft_strncmp(map[i], "EA", 2) == 0)
		{
			if (f_colors)
				return (false);
			f_textures = true;
		}
		else if (ft_strncmp(map[i], "C", 1) == 0 || ft_strncmp(map[i], "F", 1) == 0)
		{
			if (!f_textures)
				return (false);
			f_colors = true;
		}
		else if (ft_strncmp(map[i], "1", 1) == 0)
		{
			if (!f_textures || !f_colors)
				return (false);
			break ;
		}
		i++;
	}
	return (true);
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

	len = find_map(parse) + 1;
	res = malloc(sizeof(char *) * (matrix_len(parse->map + len) + 1));
	i = 0;
	while (parse->map[len] && ft_strncmp(parse->map[len], "\n", ft_strlen(parse->map[len])) != 0)
	{
		res[i] = ft_strdup(parse->map[len]);
		len++;
		i++;
	}
	res[i] = NULL;
	free_matrixx(parse->map);
	parse->map = res;
}

char	**cpy_matrix(char **str)
{
	char	**res;
	int		i;

	res = malloc(sizeof(str) / sizeof(char *));
	i = 0;
	res[sizeof(str) / sizeof(char *)] = NULL;
	while (str[i])
	{
		res[i] = ft_strdup(str[i]);
		i++;
	}
	return (res);
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
	flood->w = w;
	flood->h = i;
}

int		get_n_cords(char **map)
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

	flood->s_cord = malloc(sizeof(t_point) * size);
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
}

void	init_flood(t_parse *parse)
{
	t_flood	flood;

	get_w_h(&flood, parse->map);
	get_cords(&flood, get_n_cords(parse->map), parse->map);
}



//todo 
//I have a structure for the flood fill
//The main task is to find the way to find the boxes on which I should do the flood_fill
//If I will give up I will just do the stupid infite flood_fill
