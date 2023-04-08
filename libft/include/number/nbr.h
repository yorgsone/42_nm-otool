/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:44:17 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:44:18 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBR_H
# define NBR_H
# include "../libft.h"

int					*ft_intdup(const int *tab, int size);
int					*ft_intndup(const int *t, int n);
int					*ft_intcpy(int *dst, const int *src, int len);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				sort_int_tab(int *tab, int size);

#endif
