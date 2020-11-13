/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:33:06 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:33:08 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static int	print_fat_header(t_filetype *fat, struct fat_arch *archs,
	size_t narchs)
{
	void		*fat_arch;
	uint32_t	i;

	ft_printf("Fat headers\n");
	ft_printf("fat_magic 0x%x\nnfat_arch %"PRIu32"\n", swap32(fat->big_endian,\
	((struct fat_header*)fat->start)->magic), narchs);
	fat_arch = fat->start + sizeof(struct fat_header);
	i = 0;
	while (i < narchs)
	{
		if (check_oflow(fat, fat_arch + 1))
			return (-1);
		ft_printf("%s% d\n", "architecture", i);
		ft_printf("    %s %d\n", "cputype", archs[i].cputype);
		ft_printf("    %s %d\n", "cpusubtype",\
		archs[i].cpusubtype & ~CPU_SUBTYPE_MASK);
		ft_printf("    %s 0x%x\n", "capabilities",\
		(archs[i].cpusubtype & CPU_SUBTYPE_MASK) >> 24);
		ft_printf("    %s %u\n", "offset", archs[i].offset);
		ft_printf("    %s %u\n", "size", archs[i].size);
		ft_printf("    %s 2^%u (%u)\n", "align",\
		archs[i].align, ft_pow2(2, 12));
		i++;
	}
	return (1);
}

static int	do_fat(t_filetype *mach, t_filetype *file,
const NXArchInfo *tmp_arch_info, const NXArchInfo *local_arch)
{
	if (chk_flag(FLAG_L, file->flags) || chk_flag(FLAG_T, file->flags))
	{
		ft_printf("%s", mach->name);
		(local_arch) ? ft_printf(":\n") :
		ft_printf("( for architecture %s):\n", tmp_arch_info->name);
		if (print_long_mach_o(mach, file->flags, file) != 1)
			return (-1);
	}
	else if (chk_flag(FLAG_H, file->flags))
		print_macho_header(mach, mach->start);
	return (1);
}

static int	inner_fat(void *m_hdr, t_filetype *mach,
const NXArchInfo *local_arch, t_filetype *file)
{
	cpu_type_t			cpu_type;
	cpu_subtype_t		cpu_subtype;
	const NXArchInfo	*tmp_arch_info;

	mach->start = m_hdr;
	if (is_macho(*(uint32_t *)m_hdr, mach))
	{
		mach->size = swap32(mach->big_endian, ((t_mhdr)m_hdr)->sizeofcmds);
		mach->end = mach->start + mach->size;
		if (check_oflow(file, mach->start) || check_oflow(file, mach->end))
			return (-1);
		cpu_type = ft_bswap_int32(mach->big_endian, ((t_mhdr)m_hdr)->cputype);
		cpu_subtype = ft_bswap_int32(mach->big_endian,\
		((t_mhdr)m_hdr)->cpusubtype) & ~CPU_SUBTYPE_MASK;
		if ((!local_arch) || (local_arch && local_arch->cputype == cpu_type &&
		local_arch->cpusubtype == cpu_subtype))
		{
			if (!local_arch)
				tmp_arch_info = NXGetArchInfoFromCpuType(cpu_type, cpu_subtype);
			if (do_fat(mach, file, tmp_arch_info, local_arch) == -1)
				return (-1);
		}
	}
	return (1);
}

static int	print_macho_fat(t_filetype *fat, uint32_t nfat_arch,
const NXArchInfo *best_arch)
{
	void		*m_hdr;
	void		*fat_arch;
	uint32_t	i;
	t_filetype	mach;

	init_struct(&mach);
	fat_arch = fat->start + sizeof(struct fat_header);
	mach.name = fat->name;
	m_hdr = fat->start + swap32(fat->big_endian, ((t_fa*)fat_arch)->offset);
	i = 0;
	while (i < nfat_arch)
	{
		if (inner_fat(m_hdr, &mach, best_arch, fat) != 1)
			return (-1);
		fat_arch = fat_arch + sizeof(t_fa);
		m_hdr = fat->start + swap32(fat->big_endian, ((t_fa*)fat_arch)->offset);
		mach.start = m_hdr;
		i++;
	}
	return (1);
}

int			handle_fat(t_filetype *fat, uint8_t fs)
{
	uint32_t			n_arch;
	struct fat_arch		*fat_archs;
	const NXArchInfo	*local_arch;

	fat_archs = NULL;
	local_arch = NULL;
	fat->flags = fs;
	n_arch = swap32(fat->big_endian, ((t_fh*)fat->start)->nfat_arch);
	if (n_arch <= 0)
		return (error_ret(-3, fat->name, "not archs found"));
	if (check_oflow(fat, fat->start + sizeof(struct fat_arch)))
		return (error_ret(-2, fat->name, NULL));
	if (!(fat_archs = get_archs(fat_archs, fat, n_arch)))
		return (error_ret(-3, fat->name, "arch error"));
	local_arch = get_local_arch(fat_archs, n_arch, NULL, NULL);
	if (chk_flag(FLAG_F, fs))
		if (print_fat_header(fat, fat_archs, n_arch) != 1)
			return (error_ret(-2, fat->name, NULL));
	if (chk_flag(FLAG_L, fs) || chk_flag(FLAG_H, fs) || chk_flag(FLAG_T, fs))
		if (print_macho_fat(fat, n_arch, local_arch) != 1)
			return (error_ret(-2, fat->name, NULL));
	free_nxinfo(local_arch, NULL);
	if (fat_archs)
		free(fat_archs);
	return (1);
}
