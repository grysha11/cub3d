/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:03:15 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/10 20:17:35 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while ((s[i] != '\0') && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

void	free_matrix(char **matrix, size_t i)
{
	while (i > 0)
	{
		i--;
		free(matrix[i]);
	}
	free(matrix);
}

char	**ft_split2(const char *s, char c, char **matrix, size_t words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		matrix[i] = ft_substr(s, j, word_len((&s[j]), c));
		if (matrix[i] == NULL)
		{
			free_matrix(matrix, i);
			return (NULL);
		}
		while (s[j] != '\0' && s[j] != c)
			j++;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

char	**ft_split(const char *s, char c)
{
	char	**matrix;
	size_t	words;

	if (s == NULL)
		return (NULL);
	words = ft_count(s, c);
	matrix = malloc(sizeof(char *) * (words + 1));
	if (matrix == NULL)
		return (NULL);
	matrix = ft_split2(s, c, matrix, words);
	return (matrix);
}

// #include <stdio.h>

// int main()
// {
//     // Test case 1
//     const char *str1 = "Hello,world,this,is,a,test";
//     char **result1 = ft_split(str1, ',');

//     // Print the result of test case 1
//     printf("Test case 1:\n");
//     for (int i = 0; result1[i] != NULL; i++)
//     {
//         printf("%s\n", result1[i]);
//         free(result1[i]); // Free each substring
//     }
//     free(result1); // Free the array of pointers

//     // Test case 2
//     const char *str2 = "one::two:::three::::four";
//     char **result2 = ft_split(str2, ':');

//     // Print the result of test case 2
//     printf("Test case 2:\n");
//     for (int i = 0; result2[i] != NULL; i++)
//     {
//         printf("%s\n", result2[i]);
//         free(result2[i]); // Free each substring
//     }
//     free(result2); // Free the array of pointers

//     // Test case 3
//     const char *str3 = "split,with,,multiple,delimiters,";
//     char **result3 = ft_split(str3, ',');

//     // Print the result of test case 3
//     printf("Test case 3:\n");
//     for (int i = 0; result3[i] != NULL; i++)
//     {
//         printf("%s\n", result3[i]);
//         free(result3[i]); // Free each substring
//     }
//     free(result3); // Free the array of pointers

//     return 0;
// }