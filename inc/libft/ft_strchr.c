/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:03:47 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/10 19:05:57 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	else
		return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	const char *str = "hAaaaAbbb";
// 	char *ptr = ft_strchr(str, 'A');

// 	printf("%s\n", ptr);

// 	return (0);
// }