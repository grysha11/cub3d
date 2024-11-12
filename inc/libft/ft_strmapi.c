/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:10:37 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/10 13:01:49 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		str[i] = f(i, *s++);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>

// char	test_func(unsigned int i, char c)
// {
// 	return (c + i);
// }

// int main(void)
// {
// 	char *str = "hello";
// 	printf("Before: %s\t", str);
// 	char *res = ft_strmapi(str, test_func);
// 	printf("After: %s\n", res);

// 	return (0);
// }