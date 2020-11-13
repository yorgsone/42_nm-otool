/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:25:45 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:25:57 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static void	print_proper_arch(const NXArchInfo *l_arch, cpu_type_t cpu_type,
cpu_subtype_t cpu_subtype, t_filetype *file)
{
	const NXArchInfo	*info;

	info = NULL;
	if (!l_arch)
		info = NXGetArchInfoFromCpuType(cpu_type, cpu_subtype);
	if (!l_arch)
		(!info) ? ft_printf("\n%s (for architecture %u):\n",
							file->name, cpu_type)
				: ft_printf("\n%s (for architecture %s):\n",
							file->name, info->name);
}

static int	inner_fat
	(void *m_hdr, t_filetype *mach,
	const NXArchInfo *l_arch, t_filetype *file)
{
	cpu_type_t			cpu_type;
	cpu_subtype_t		cpu_subtype;

	mach->start = m_hdr;
	if (check_oflow(file, mach->start))
		return (-1);
	if (is_macho(*(uint32_t *)m_hdr, mach))
	{
		mach->size = swap32(mach->big_endian, ((t_mhdr)m_hdr)->sizeofcmds);
		mach->end = mach->start + mach->size;
		if (check_oflow(file, mach->start) \
		|| check_oflow(file, mach->end))
			return (-1);
		cpu_type = ft_bswap_int32(mach->big_endian, ((t_mhdr)m_hdr)->cputype);
		cpu_subtype = ft_bswap_int32(mach->big_endian, \
		((t_mhdr)m_hdr)->cpusubtype) & ~CPU_SUBTYPE_MASK;
		if ((!l_arch) || (l_arch && l_arch->cputype == cpu_type \
		&& l_arch->cpusubtype == cpu_subtype))
		{
			print_proper_arch(l_arch, cpu_type, cpu_subtype, file);
			handle_mach_o(1, mach, file);
		}
	}
	return (1);
}

static int	iter_macho_fat
	(uint32_t nfat_arch, t_filetype *file, const NXArchInfo *l_arch)
{
	void		*fat_arch;
	void		*m_hdr;
	uint32_t	i;
	t_filetype	mach;

	i = 0;
	fat_arch = file->start + sizeof(struct fat_header);
	init_struct(&mach);
	m_hdr = file->start + \
		swap32(file->big_endian, ((struct fat_arch*)fat_arch)->offset);
	mach.name = file->name;
	while (i < nfat_arch)
	{
		if (inner_fat(m_hdr, &mach, l_arch, file) != 1)
			return (-1);
		fat_arch = fat_arch + sizeof(struct fat_arch);
		m_hdr = file->start + \
		swap32(file->big_endian, ((struct fat_arch*)fat_arch)->offset);
		i++;
	}
	return (1);
}

int			handle_fat(t_filetype *file)
{
	uint32_t			nfat_arch;
	struct fat_arch		*fat_archs;
	const NXArchInfo	*l_arch;

	fat_archs = NULL;
	l_arch = NULL;
	nfat_arch = swap32(file->big_endian, \
	((struct fat_header*)file->start)->nfat_arch);
	if (nfat_arch < 0)
		return (error_ret(-3, file->name, ""));
	if (check_oflow(file, file->start + sizeof(struct fat_arch)))
		return (error_ret(-2, file->name, NULL));
	fat_archs = get_archs(fat_archs, file, nfat_arch);
	if (!fat_archs)
		return (error_ret(-3, file->name, "arch error"));
	l_arch = get_local_arch(fat_archs, nfat_arch, NULL, NULL);
	if (iter_macho_fat(nfat_arch, file, l_arch) != 1)
		return (error_ret(-2, file->name, NULL));
	free_nxinfo(l_arch, NULL);
	if (fat_archs)
		free(fat_archs);
	return (1);
}
