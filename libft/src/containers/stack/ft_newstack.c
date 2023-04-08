/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:47:49 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 13:48:02 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

t_st	*ft_newstack(int data, int size)
{
	t_st *stack;

	if (!(stack = (t_st *)ft_memalloc(sizeof(t_st))))
		return (NULL);
	stack->size = size;
	stack->data = data;
	stack->next = NULL;
	return (stack);
}
