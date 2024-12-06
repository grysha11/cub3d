//just go thru string
//check that first word is C or F
//then just go thru numbers delimited by ',' and ' '
//if count is bigger throw an error

#include "../cub3d.h"

void	format_color(t_parse *parse, char *str)
{
	(void)parse;
	int		c[3];
	char	color;
	int		i;
	char	**res;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	i++;
	res = ft_split(str + i, ',');
	
	if (matrix_len(res) == 3)
	{
		c[0] = ft_atoi(res[0]);
		c[1] = ft_atoi(res[1]);
		c[2] = ft_atoi(res[2]);
	}
}

void	parse_colors(t_parse *parse)
{
	int	i;
	int	count;

	count = 0;
	while (count < 2)
	{
		i = find_str(parse->map);
		format_color(parse, parse->map[i]);
		count++;
	}
}
