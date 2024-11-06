/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:10:17 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 14:32:52 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
	{
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}

// int main(void)
// {
// 	char src[] = "guys";
// 	char dst[20] = "hello ";
// 	size_t	size = ft_strlcat(dst, src, sizeof(dst));
// 	printf("%ld\n", size);
// 	printf("%s\n", dst);
// 	printf("%s\n", src);
//
// 	return (0);
// }