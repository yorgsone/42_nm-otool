/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:44:01 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:52:44 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H
# include "../libft.h"

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int i);
char		*ft_ftoa(double nb, int prc);
char		*ft_utoa_base(unsigned long long val, int base);
char		*ft_itoa_base(int value, int base);
char		*ft_convertunicode(wchar_t c);
long int	ft_atol(const char *str);

#endif
