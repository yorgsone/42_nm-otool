/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:23:55 by gemaroul          #+#    #+#             */
/*   Updated: 2018/11/16 14:26:00 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "../../libft.h"

typedef	struct		s_st
{
	int			size;
	int			data;
	int			bot;
	struct s_st *next;
}					t_st;

# define LIM (long)INT_MIN - 1

int					ft_isfull(t_st *stack);
int					ft_isempty(t_st *root);
int					ft_pop(t_st **root);
int					ft_peek(t_st *root);
t_st				*ft_push(t_st **root, int data, int size);
t_st				*ft_newstack(int data, int size);

#endif
