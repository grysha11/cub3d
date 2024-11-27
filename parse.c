/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/27 17:27:00 by hzakharc         ###   ########.fr       */
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

void	assign_tab(char *src, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\t' || src[i] == '\v')
		{
			dst[j] = ' ';
			dst[j++] = ' ';
			dst[j++] = ' ';
			dst[j++] = ' ';
			i++;
		}
		else
		{
			dst[j] = src[i];
			j++;
			i++;
		}
	}
	dst[j] = '\0';
}

char	*tab_alloc(char *src)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (src[i])
	{
		if (src[i] == '\t' || src[i] == '\v')
			len += 4;
		i++;
		len++;
	}
	res = malloc(sizeof(char) * (len + 1));
	assign_tab(src, res);
	return (res);
}

void	tab_trim(t_parse *parse)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (matrix_len(parse->map) + 1));
	while (parse->map[i])
	{
		res[i] = tab_alloc(parse->map[i]);
		i++;
	}
	res[i] = NULL;
	// printf("ORIGINAL STR IS: \n\n");
	// for (int i = 0; parse->map[i]; i++)
	// 	printf("STRLEN IS %zu\tSTRING IS %s\n", ft_strlen(parse->map[i]), parse->map[i]);
	// printf("RESULT IS: \n\n");
	// for (int i = 0; res[i]; i++)
	// 	printf("STRLEN IS %zu\tSTRING IS %s\n", ft_strlen(res[i]), res[i]);
	free_matrixx(parse->map);
	parse->map = res;
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
	return (i - 1);
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
			if (parse->map[i][j] != '0' && parse->map[i][j] != '1' && parse->map[i][j] != ' ')
			{
				parse->dir = parse->map[i][j];
				printf("parse->player: %c\n", parse->map[i][j]);
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

	res = malloc(sizeof(char *) * (matrix_len(str) + 1));
	i = 0;
	while (str[i])
	{
		res[i] = ft_strdup(str[i]);
		i++;
	}
	res[i] = NULL;
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
	flood->size.x = w + 1;
	flood->size.y = i;
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

bool	neighbour(char **map, t_point size, t_point start)
{
	int	i;
	t_point	c[4];
	
	c[0] = (t_point){start.x, start.y - 1};
	c[1] = (t_point){start.x, start.y + 1};
	c[2] = (t_point){start.x - 1, start.y};
	c[3] = (t_point){start.x + 1, start.y};
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
		if (start.y >= size.y - 1 || start.y == 0 || start.x == 0 || start.x >= size.x - 1)
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
		err_inc_parse("Map is not closed");
		exit(1);
	}
	free(flood.s_cord);
	free_matrixx(flood.map);
}
