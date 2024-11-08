/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:41:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/08 16:13:11 by hzakharc         ###   ########.fr       */
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
