/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:11:04 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/10 19:02:11 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		sub[i++] = s[start++];
	}
	sub[i] = '\0';
	return (sub);
}

// #include <stdio.h>

// int main(void)
// {
// 	const char *s = "hello everyone\n";
// 	char *sub = ft_substr(s, 3, 40);

// 	printf("%s", sub);

// 	return (0);
// }