/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/09 16:39:18 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (ft_strlen(av[1]) >= 4 && ft_strncmp(av[1]
			+ ft_strlen(av[1]) - 4, ext, 4) == 0)
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
		free_parse(parse);
		err_inc_parse("Could't open the .cub file");
		exit(1);
	}
	parse->map = ft_get_file(fd, 0);
	if (!parse->map)
	{
		close(fd);
		free_parse(parse);
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
