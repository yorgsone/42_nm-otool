/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfbuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:41:41 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:41:42 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_tmp(t_print *sprint)
{
	int tmp;

	tmp = ft_atoi(sprint->nulls);
	tmp = (*(sprint->nulls) != '0' && tmp == 0) ? -1 : tmp;
	while (ft_isdigit(*(sprint->nulls)))
		(sprint->nulls)++;
	(sprint->nulls)++;
	return (tmp);
}

int			ft_printbuf(t_print *sprint)
{
	int		len;
	int		tlen;
	char	*tmp;
	char	*nulls;

	tmp = sprint->buf;
	nulls = sprint->nulls;
	tlen = ft_strlen(tmp);
	while ((len = ft_tmp(sprint)) != -1)
	{
		tlen++;
		write(1, tmp, len);
		write(1, "\0", 1);
		tmp = tmp + len;
	}
	write(1, tmp, ft_strlen(tmp));
	ft_freestruct(sprint, nulls);
	return (tlen);
}
