/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:11:16 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 14:53:38 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int i)
{
	if (i >= 'a' && i <= 'z')
	{
		return (i - 32);
	}
	return (i);
}

// int main(void)
// {
// 	char c = 'a';

// 	printf("%c", ft_toupper(c));

// 	return (0);
// }