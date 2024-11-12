/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:59:19 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 18:49:29 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*p;

	if (count == 0 || size == 0)
		return (malloc(0));
	total = count * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, total);
	return (p);
}

// int main(void)
// {
// 	int *nums = ft_calloc(5, sizeof(int));
// 	char *str = ft_calloc(15, sizeof(char));
// 	int	 *zero_arr = ft_calloc(0, sizeof(int));

// 	free(nums);
// 	free(str);
// 	free(zero_arr);

// 	return (0);
// }