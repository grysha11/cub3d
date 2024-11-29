/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/29 18:30:10 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	free_matrixx(parse->map);
	parse->map = res;
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
	int	y;

	y = 0;
	i = find_map(parse);
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] != '0' && parse->map[i][j] != '1' && parse->map[i][j] != ' ')
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
