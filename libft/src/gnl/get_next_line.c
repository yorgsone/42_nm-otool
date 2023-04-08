/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 02:06:09 by gemaroul          #+#    #+#             */
/*   Updated: 2018/05/01 10:24:21 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static unsigned int	aftersave(char *stock)
{
	unsigned int	i;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i);
}

static char			*glue(char *s1, char *s2, size_t len)
{
	char	*str;
	char	*tmp;
	int		nb;

	nb = ft_strlen(s1) + ++len;
	str = ft_strnew(nb);
	tmp = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2 && --len > 0)
		*str++ = *s2++;
	*str = '\0';
	return (str - (str - tmp));
}

static char			*b4_after_cpy(char *stock)
{
	if (ft_strchr(stock, '\n'))
	{
		ft_strcpy(stock, ft_strchr(stock, '\n') + 1);
		return (stock);
	}
	if (aftersave(stock) > 0)
	{
		ft_strcpy(stock, ft_strchr(stock, '\0'));
		return (stock);
	}
	return (NULL);
}

int					get_next_line(const int fd, char **line)
{
	static char	*stock[101];
	char		buf[BUFF_SIZE + 1];
	char		*ptr;
	int			gear;

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (READ_ERROR);
	if (!(stock[fd]) && !(stock[fd] = ft_strnew(0)))
		return (GNL_ERROR);
	while (!(ft_strchr(stock[fd], '\n')) &&
	(gear = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[gear] = '\0';
		ptr = stock[fd];
		stock[fd] = glue(ptr, buf, gear);
		free(ptr);
	}
	*line = ft_strsub(stock[fd], 0, aftersave(stock[fd]));
	if (!b4_after_cpy(stock[fd]))
		return (GNL_FINISHED);
	return (GNL_OK);
}
