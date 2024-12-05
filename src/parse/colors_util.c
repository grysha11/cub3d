/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:03:07 by hzakharc          #+#    #+#             */
/*   Updated: 2024/12/05 16:05:53 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// bool	have_to_trim(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ',')
// 			break ;
// 		i++;
// 	}
// 	while (str[j])
// 	{
// 		if (ft_isdigit(str[j]) == true)
// 			break ;
// 		j++;
// 	}
// 	if (str[i] == '\0')
// 		return (true);
// 	if (i < j)
// 		return (true);
// 	return (false);
// }

// void	trim_spaces(int start, t_parse *parse)
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	i = 0;
// 	while (!ft_isdigit(parse->map[start][i]) && parse->map[start][i])
// 		i++;
// 	if (ft_strchr(parse->map[start] + i, ' ') != NULL)
// 	{
// 		i = 0;
// 		j = 0;
// 		res = malloc(sizeof(char) * ft_strlen(parse->map[start] + 1));
// 		while (!ft_isdigit(parse->map[start][i]) && parse->map[start][i])
// 		{
// 			res[j] = parse->map[start][i];
// 			i++;
// 			j++;
// 		}
// 		while (parse->map[start][i])
// 		{
// 			if (have_to_trim(parse->map[start] + i) == true)
// 			{
// 				if (parse->map[start][i] != ' ')
// 				{
// 					res[j] = parse->map[start][i];
// 					j++;
// 				}
// 			}
// 			else
// 			{
// 				res[j] = parse->map[start][i];
// 				j++;
// 			}
// 			i++;
// 		}
// 		res[j] = '\0';
// 		printf("%s\n", res);
// 		free(parse->map[start]);
// 		parse->map[start] = ft_strdup(res);
// 		free(res);
// 	}
// }

int		len_without_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			j++;
		i++;
	}
	return (j);
}

char	*trim_space_str(char *str)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) + (len_without_spaces(str) + 1));
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

bool	matrix_check(char **res)
{
	int	i;

	i = 0;
	if (matrix_len(res) == 1)
		return (false);
	while (res[i])
	{
		if (i % 2 != 0)
			if (ft_strncmp(res[i], ",", ft_strlen(res[i]) + 1) != 0)
				return (false);
		i++;
	}
	return (true);
}

void	trim_spaces(int start, t_parse *parse)
{
	char	**res;
	char	*res2;
	char	*smth;
	int		i;

	i = 0;
	while (!ft_isdigit(parse->map[start][i]) && parse->map[start][i])
		i++;
	res = ft_split(parse->map[start] + i, ' ');
	for (int i = 0; res[i]; i++)
		printf("%d%s\n", i, res[i]);
	if (matrix_check(res))
	{
		res2 = trim_space_str(parse->map[start] + i);
		smth = ft_substr(parse->map[start], 0, i);
		free(parse->map[start]);
		parse->map[start] = ft_strjoin(smth, res2);
		free(res2);
		free(smth);
		free_matrixx(res);
	}
	else
		free_matrixx(res);
}
