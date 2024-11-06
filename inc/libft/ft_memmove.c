/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:01:25 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 13:36:25 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (dst);
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len--)
			ptr_dst[len] = ptr_src[len];
	}
	else
	{
		while (len--)
			*ptr_dst++ = *ptr_src++;
	}
	return (dst);
}

// int main(void)
// {
// 	char *src = "hello";
// 	char dst[10];

// 	ft_memmove(dst, src, sizeof(src));

// 	printf("%s\n", dst);

// 	return (0);
// }