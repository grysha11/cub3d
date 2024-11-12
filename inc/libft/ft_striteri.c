/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:04:09 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/11 14:34:20 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		(*f)(i, (s + i));
		i++;
	}
}

// #include <ctype.h>
//
// void	ft_upper_case(unsigned int i, char *str)
// {
// 	*str = toupper(*str)
// }

// int main(void)
// {
// 	char str[] = "hello";

// 	printf("%s\n", str);
// 	ft_striteri(str, ft_upper_case);
// 	printf("%s\n", str);

// 	return (0);
// }