/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:26:57 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:27:04 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

# if __MACH__
static int	inner_ar
	(void *ar_hdr, void *m_hdr, t_filetype *ar, t_filetype *mach)
{
	int		ar_name_size;
	char	o_name[100];

	ft_memset(o_name, '\0', 100);
	if (!ft_strncmp(((t_ar)ar_hdr)->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		ar_name_size = ft_atoi(&((t_ar)ar_hdr)->ar_name[ft_strlen(AR_EFMT1)]);
		ft_strncpy(o_name, m_hdr, ar_name_size);
		m_hdr = m_hdr + ar_name_size;
	}
	else
		ft_strcpy(o_name, ((t_ar)ar_hdr)->ar_name);
	if (check_oflow(ar, ar_hdr + ar_name_size))
		return (-1);
	mach->start = m_hdr;
	mach->name = o_name;
	if (is_macho(*(uint32_t *)m_hdr, mach))
	{
		mach->size = swap32(mach->big_endian, ((t_mhdr)m_hdr)->sizeofcmds);
		mach->end = mach->start + mach->size;
		ft_printf("\n%s(%s):\n", ar->name, o_name);
		if (handle_mach_o(1, mach, ar) != 1)
			return (-1);
	}
	return (1);
}
# endif

void		handle_ar(t_filetype *ar)
{
	void		*ptr;
	void		*ar_hdr;
	void		*m_hdr;
	uint64_t	sz;
	t_filetype	mach;

	ptr = ar->start + SARMAG;
	ar_hdr = ar->start + SARMAG;
	m_hdr = ar_hdr + sizeof(struct ar_hdr);
	init_struct(&mach);
	while (ar_hdr < ar->start + ar->size)
	{
		ar_hdr = ptr;
		ptr += sizeof(struct ar_hdr);
		m_hdr = ar_hdr + sizeof(struct ar_hdr);
		if (check_oflow(ar, ptr))
			return ;
		sz = ft_atoi(((struct ar_hdr*)ar_hdr)->ar_size);
		if (check_oflow(ar, ptr) || sz == 0 || check_oflow(ar, ptr + sz))
			return ;
		# if __MACH__
		if (inner_ar(ar_hdr, m_hdr, ar, &mach) != 1)
			return ;
		# endif
		ptr += sz;
	}
}
