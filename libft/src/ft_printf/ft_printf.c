/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:41:31 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/06 11:07:47 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	char		*tmp;
	char		*dup;
	char		*del;
	t_print		*sprint;

	sprint = NULL;
	if (!(sprint = ft_allocate(sprint)))
		return (-1);
	dup = ft_strdup(format);
	del = dup;
	va_start(ap, format);
	while ((tmp = ft_strchr(dup, '%')))
	{
		*tmp++ = '\0';
		sprint->buf = ft_strjoinfree(sprint->buf, sprint->buf, dup);
		if (!(dup = ft_assign(tmp, sprint, ap)))
			return (-1);
		ft_process(sprint, ap);
		sprint = ft_allocate(sprint);
	}
	sprint->buf = ft_strjoinfree(sprint->buf, sprint->buf, dup);
	free(del);
	return (ft_printbuf(sprint));
}
