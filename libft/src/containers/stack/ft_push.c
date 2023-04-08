/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:44:54 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 13:46:11 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

t_st	*ft_push(t_st **root, int data, int size)
{
	t_st *stack;

	if (!(stack = (t_st *)malloc(sizeof(t_st))))
		return (NULL);
	stack->data = data;
	if ((*root) == NULL)
		stack->bot = stack->data;
	else
		stack->bot = (*root)->bot;
	stack->size = size;
	stack->next = *root;
	*root = stack;
	return (*root);
}
