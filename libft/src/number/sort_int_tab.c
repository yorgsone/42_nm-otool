/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:37:44 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 13:40:48 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		sort_int_tab(int *tab, int size)
{
	int a;
	int i;

	a = 0;
	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			ft_swap(&tab[i], &tab[i + 1]);
			a = i;
		}
		while (a)
		{
			if (a >= 0 && a - 1 >= 0 && tab[a - 1] > tab[a])
			{
				ft_swap(&tab[a - 1], &tab[a]);
				--a;
			}
			else
				a = 0;
		}
		++i;
	}
}
