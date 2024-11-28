#include "cub3d.h"

void	err_inc_parse(char *first_message)
{
	printf("%sERROR %s: %s\n\t", COLOR_RED, first_message, COLOR);
	printf("Try: %s./cub3d map.cub%s\n", COLOR_CYAN, COLOR);
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

int		matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
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
