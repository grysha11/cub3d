/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:24:25 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/06 19:50:57 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_rgb(int *rgb, t_parse *parse, char **str)
{
	if ((rgb[0] >= 0 && rgb[0] <= 255) && (rgb[1] >= 0 && rgb[1] <= 255)
		&& (rgb[2] >= 0 && rgb[2] <= 255))
		return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	else
	{
		err_inc_parse("Incorrect color values");
		free_parse(parse);
		free_matrixx(str);
		exit(1);
	}
}

void	check_numeric(t_parse *parse, char **res)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (res[i][j])
		{
			if (!ft_isdigit(res[i][j]) && res[i][j] != ' ')
			{
				err_inc_parse("Non numeric value of RGB values");
				free_matrixx(res);
				free_parse(parse);
				exit(1);
			}
			j++;
		}
		i++;
	}
}
