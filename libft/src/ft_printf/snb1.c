/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snb1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:41:53 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:41:54 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void		ft_int(t_print *sprint, va_list ap)
{
	char			*str;
	long long int	nb;

	nb = va_arg(ap, int);
	sprint->minus = (nb < 0) ? 1 : 0;
	nb = (nb < 0) ? -nb : nb;
	sprint->nb = nb;
	str = ft_utoa_base(nb, 10);
	str = ft_applyprecision(sprint, str);
	str = ft_applywidth(sprint, str);
	str = ft_applyflags(sprint, str);
	sprint->buf = ft_strjoinfree(sprint->buf, sprint->buf, str);
	free(str);
}

void		ft_long(t_print *sprint, va_list ap)
{
	char			*str;
	long long int	nb;

	nb = va_arg(ap, long int);
	sprint->minus = (nb < 0) ? 1 : 0;
	nb = (nb < 0) ? -nb : nb;
	sprint->nb = nb;
	str = ft_utoa_base(nb, 10);
	str = ft_applyprecision(sprint, str);
	str = ft_applywidth(sprint, str);
	str = ft_applyflags(sprint, str);
	sprint->buf = ft_strjoinfree(sprint->buf, sprint->buf, str);
	free(str);
}

void		ft_longlong(t_print *sprint, va_list ap)
{
	char			*str;
	long long int	nb;

	nb = va_arg(ap, long long int);
	sprint->minus = (nb < 0) ? 1 : 0;
	nb = (nb < 0) ? -nb : nb;
	sprint->nb = nb;
	str = ft_utoa_base(nb, 10);
	str = ft_applyprecision(sprint, str);
	str = ft_applywidth(sprint, str);
	str = ft_applyflags(sprint, str);
	sprint->buf = ft_strjoinfree(sprint->buf, sprint->buf, str);
	free(str);
}

void		ft_intmax_t(t_print *sprint, va_list ap)
{
	char			*str;
	long long int	nb;

	nb = va_arg(ap, long long);
	sprint->minus = (nb < 0) ? 1 : 0;
	nb = (nb < 0) ? -nb : nb;
	sprint->nb = nb;
	str = ft_utoa_base(nb, 10);
	str = ft_applyprecision(sprint, str);
	str = ft_applywidth(sprint, str);
	str = ft_applyflags(sprint, str);
	sprint->buf = ft_strjoinfree(sprint->buf, sprint->buf, str);
	free(str);
}
