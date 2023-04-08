/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:43:40 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:43:42 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHR_H
# define CHR_H
# include "../libft.h"

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);

/*
** Wide Char
*/

size_t				ft_wcharlen(unsigned wc);

#endif
