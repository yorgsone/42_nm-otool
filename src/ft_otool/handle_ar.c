/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:30:46 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:30:50 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static void	print_ar_header(t_filetype *ar)
{
	void *ar_hdr;

	ar_hdr = ar->start + SARMAG;
	ft_printf("Archive : %s\n", ar->name);
	while (ar_hdr < ar->start + ar->size)
	{
		ft_printf("0%.*s ", ft_wordlen(((t_ar)ar_hdr)->ar_mode, ' '),\
		((t_ar)ar_hdr)->ar_mode);
		ft_printf("%.*s/", ft_wordlen(((t_ar)ar_hdr)->ar_uid, ' '),\
		((t_ar)ar_hdr)->ar_uid);
		ft_printf("%.*s ", 6 - ft_wordlen(((t_ar)ar_hdr)->ar_size, ' ') +\
		ft_wordlen(((t_ar)ar_hdr)->ar_gid, ' '), ((t_ar)ar_hdr)->ar_gid);
		ft_printf("%.*s ", ft_wordlen(((t_ar)ar_hdr)->ar_size, ' '),\
		((t_ar)ar_hdr)->ar_size);
		ft_printf("%.*s ", ft_wordlen(((t_ar)ar_hdr)->ar_date, ' '),\
		((t_ar)ar_hdr)->ar_date);
		ft_printf("%.*s\n", ft_wordlen(((t_ar)ar_hdr)->ar_name, ' '),\
		((t_ar)ar_hdr)->ar_name);
		ar_hdr = ar_hdr + sizeof(struct ar_hdr) +\
		ft_atoi(((t_ar)ar_hdr)->ar_size);
	}
}

#if __MACH__
static int	do_options(t_filetype *ar, t_filetype *mach,
void *macho_header, const char *o_name)
{
	mach->flags = ar->flags;
	mach->start = macho_header;
	if (is_macho(*(uint32_t *)macho_header, mach))
	{
		mach->size = swap32(mach->big_endian,\
		((struct mach_header*)macho_header)->sizeofcmds);
		mach->end = mach->start + mach->size;
		if (chk_flag(FLAG_L, ar->flags) || chk_flag(FLAG_T, ar->flags))
		{
			ft_printf("%s(%s):\n", ar->name, o_name);
			if (print_long_mach_o(mach, ar->flags, ar) != 1)
				return (-1);
		}
		else if (chk_flag(FLAG_H, ar->flags))
			print_macho_header(mach, macho_header);
	}
	return (1);
}

static int	print_macho_ar(t_filetype *ar, uint8_t flags,
void *ar_hdr, void *m_hdr)
{
	int			ar_name_size;
	char		o_name[100];
	t_filetype	mach;

	init_struct(&mach);
	if (!chk_flag(FLAG_A, flags))
		ft_printf("Archive : %s\n", ar->name);
	while (ar_hdr < ar->start + ar->size)
	{
		ft_memset(o_name, '\0', 100);
		if (!ft_strncmp(((t_ar)ar_hdr)->ar_name, AR_1, ft_strlen(AR_1)))
		{
			ar_name_size = ft_atoi(&((t_ar)ar_hdr)->ar_name[ft_strlen(AR_1)]);
			ft_strncpy(o_name, m_hdr, ar_name_size);
			m_hdr = m_hdr + ar_name_size;
		}
		else
			ft_strcpy(o_name, ((t_ar)ar_hdr)->ar_name);
		if (do_options(ar, &mach, m_hdr, o_name) != 1)
			return (-1);
		ar_hdr = ar_hdr + sizeof(struct ar_hdr) +\
		ft_atoi(((t_ar)ar_hdr)->ar_size);
		m_hdr = ar_hdr + sizeof(struct ar_hdr);
	}
	return (1);
}


void		handle_ar(t_filetype *ar, uint8_t flags)
{
	ar->flags = flags;
	if (chk_flag(FLAG_A, flags))
		print_ar_header(ar);
	if (chk_flag(FLAG_L, flags) || chk_flag(FLAG_H, flags) ||
	chk_flag(FLAG_T, flags))
		if (print_macho_ar(ar, flags, ar->start + SARMAG,\
		(ar->start + SARMAG) + sizeof(struct ar_hdr)) != 1)
			error_ret(-2, ar->name, NULL, NULL);
}
#endif