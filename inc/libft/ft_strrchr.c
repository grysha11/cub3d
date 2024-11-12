/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:10:54 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/10 19:06:40 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if (s[i] == (char)c)
		return ((char *)s + i);
	while (i > 0)
	{
		if (s[i - 1] == (char)c)
		{
			return ((char *)s + i - 1);
		}
		--i;
	}
	if (s[i] == (char)c)
		return ((char *)s + i - 1);
	else
		return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	const char *str = "hAaaaAbbz";
// 	char *ptr = ft_strrchr(str, 'z');

// 	printf("%s\n", ptr);

// 	return (0);
// }