/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:01:12 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 13:27:51 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

// int main(void)
// {
// 	char *string1 = "hello";
// 	char *string2 = "heLlo";
// 	int res = ft_memcmp(string1, string2, sizeof(string1));

//     int i = 100;
//     int j = 111;

//     int res2 = ft_memcmp(&i, &j, sizeof(i));

// 	printf("%d\n", res);
//     printf("%d\n", res2);

// 	return (0);
// }