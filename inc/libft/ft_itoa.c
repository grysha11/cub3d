/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:00:05 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/09 19:16:48 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_number_size(int nb)
{
	unsigned int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		len += 1;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	len;

	len = ft_number_size(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nb = (unsigned int)(-n);
	}
	else
		nb = (unsigned int)n;
	if (n == 0)
		str[0] = '0';
	while (nb != 0)
	{
		str[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

// #include <stdio.h>

// int main(void)
// {
// 	char *str;

// 	str = ft_itoa(-2147483648);
// 	printf("%s\n", str);

// 	return (0);
// }