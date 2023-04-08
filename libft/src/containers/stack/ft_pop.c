/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:46:36 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 13:47:23 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

int	ft_pop(t_st **root)
{
	t_st	*tmp;
	int		i;

	tmp = *root;
	i = tmp->data;
	*root = tmp->next;
	tmp->next = NULL;
	tmp == NULL ? 0 : free(tmp);
	return (i);
}
