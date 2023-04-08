/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:43:21 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:43:23 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"

typedef struct	s_print
{
	char				*buf;
	char				type;
	char				*flags;
	char				*size;
	int					m_width;
	int					prc;
	int					minus;
	int					valid;
	unsigned long long	nb;
	char				*nulls;
}				t_print;

int				ft_printf(const char *str, ...);
char			*ft_assign(char *str, t_print *sprint, va_list ap);
void			ft_process(t_print *sprint, va_list ap);
void			ft_string(t_print *sprint, va_list ap);
void			ft_char(t_print *sprint, va_list ap);
void			ft_handledi(t_print *sprint, va_list ap);
void			ft_handleoux(t_print *sprint, va_list ap);
void			ft_handlef(t_print *sprint, va_list ap);
void			ft_int(t_print *sprint, va_list ap);
void			ft_long(t_print *sprint, va_list ap);
void			ft_longlong(t_print *sprint, va_list ap);
void			ft_intmax_t(t_print *sprint, va_list ap);
void			ft_schar(t_print *sprint, va_list ap);
void			ft_short(t_print *sprint, va_list ap);
void			ft_size_t(t_print *sprint, va_list ap);
void			ft_ulonglong(t_print *sprint, va_list ap);
void			ft_ulong(t_print *sprint, va_list ap);
void			ft_uchar(t_print *sprint, va_list ap);
void			ft_ushort(t_print *sprint, va_list ap);
void			ft_uintmax_t(t_print *sprint, va_list ap);
void			ft_usize_t(t_print *sprint, va_list ap);
void			ft_uint(t_print *sprint, va_list ap);
void			ft_pointer(t_print *sprint, va_list ap);
void			ft_wchar_t(t_print *sprint, va_list ap);
void			ft_wint_t(t_print *sprint, va_list ap);
char			*ft_applywidth(t_print *sprint, char *str);
char			*ft_applyprecision(t_print *sprint, char *str);
char			*ft_applyflags(t_print *sprint, char *str);
int				ft_printbuf(t_print *sprint);
void			ft_initvalues(t_print *sprint);
void			ft_freestruct(t_print *sprint, char *nulls);
t_print			*ft_allocate(t_print *oprint);

#endif
