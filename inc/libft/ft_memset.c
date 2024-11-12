/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:02:15 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/09 15:46:31 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	char	*str;

	str = (char *)ptr;
	while (len > 0)
	{
		*str = value;
		str++;
		len--;
	}
	return (ptr);
}

// #include <stdio.h>

// int main(void)
// {
// 	char str[30] = "AaaaaaB";
// 	printf("%s\n", str);

// 	ft_memset(str + 1, 'A',sizeof(char) * 5);
// 	printf("%s\n", str);

// 	int arr[10];

// 	ft_memset(arr, 0, sizeof(int) * 10);
// 	int i = 0;
// 	while (i < 10)
// 	{
// 		printf("%d ", arr[i]);
// 		i++;
// 	}
// 	printf("\n");

// 	return (0);
// }