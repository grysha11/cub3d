/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:59:11 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 13:16:06 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// 	int i = 0;

// 	while (i < 10)
// 	{
// 		printf("%d ", arr[i]);
// 		i++;
// 	}
// 	ft_bzero(arr, 10);
// 	while (i < 10)
// 	{
// 		printf("%d ", arr[i]);
// 		i++;
// 	}
// 	printf("\n");

// 	return (0);
// }