/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:25:03 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/08 15:52:18 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include "../libft/libft.h"

char	*ft_get_static(char *str, char buf[BUFFER_SIZE], int len)
{
	char	*tmp;

	buf[len] = '\0';
	if (!str)
		str = ft_strdup(buf);
	else if (str)
	{
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
	}
	return (str);
}

char	*ft_stock_line(char *str, char **line)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\n' && str[i])
		i++;
	if (i < len)
	{
		*line = ft_substr(str, 0, i);
		tmp = str;
		str = ft_substr(str, i + 1, len);
		free(tmp);
	}
	else
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

int	gnl(int fd, char **line)
{
	int				len;
	char			buf[BUFFER_SIZE + 1];
	static char		*str;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	len = read(fd, buf, BUFFER_SIZE);
	while (len > 0)
	{
		str = ft_get_static(str, buf, len);
		if (ft_strchr(str, '\n'))
			break ;
		len = read(fd, buf, BUFFER_SIZE);
	}
	if (!str)
	{
		*line = ft_strdup("");
		return (0);
	}
	str = ft_stock_line(str, line);
	if (!str)
		return (0);
	return (1);
}

char	**ft_get_file(int fd, int lvl)
{
	char	*line;
	char	**tab;

	line = NULL;
	if (gnl(fd, &line) == 1)
		tab = ft_get_file(fd, lvl + 1);
	else
	{
		tab = malloc(sizeof(char *) * (lvl + 2));
		tab[lvl + 1] = NULL;
	}
	tab[lvl] = line;
	return (tab);
}
