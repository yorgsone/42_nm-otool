/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:42:06 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:42:07 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_freestruct(t_print *sprint, char *nulls)
{
	free(sprint->buf);
	free(nulls);
	free(sprint->flags);
	free(sprint->size);
	free(sprint);
}

void	ft_initvalues(t_print *sprint)
{
	sprint->m_width = 0;
	sprint->prc = -1;
	sprint->minus = 0;
	sprint->type = '\0';
	sprint->valid = 1;
}

t_print	*ft_allocate(t_print *oprint)
{
	t_print *sprint;

	if (!(sprint = (t_print*)malloc(sizeof(*sprint))))
		return (NULL);
	if (!(sprint->flags = ft_strnew(0)))
		return (NULL);
	if (!(sprint->size = ft_strnew(0)))
		return (NULL);
	if (!oprint)
	{
		if (!(sprint->buf = ft_strnew(0)))
			return (NULL);
		if (!(sprint->nulls = ft_strnew(0)))
			return (NULL);
	}
	else
	{
		sprint->buf = ft_strdup(oprint->buf);
		sprint->nulls = ft_strdup(oprint->nulls);
		ft_freestruct(oprint, oprint->nulls);
	}
	ft_initvalues(sprint);
	return (sprint);
}
