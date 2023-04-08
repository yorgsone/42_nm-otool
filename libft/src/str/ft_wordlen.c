/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:54:11 by gemaroul          #+#    #+#             */
/*   Updated: 2018/04/08 14:54:12 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

unsigned int	ft_wordlen(char const *s, char c)
{
	unsigned int	len;

	len = 0;
	while (s && s[len] != c)
		len++;
	return (len);
}
