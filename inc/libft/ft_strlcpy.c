/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:10:21 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 14:39:01 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		if (i < size)
		{
			dst[i] = '\0';
		}
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

// int main(void)
// {
// 	char dst[10];
// 	char *src = "hello";

// 	ft_strlcpy(dst, src, sizeof(dst));

// 	printf("%s", dst);

// 	return (0);
// }