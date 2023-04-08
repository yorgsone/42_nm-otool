/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:34:24 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:34:26 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shared.h"

#if __MACH__
static int		ar_ok(struct fat_arch *arch)
{
	if ((arch->cputype == 0 && arch->cpusubtype == 0) \
		|| arch->offset == 0 || arch->offset % ft_pow2(2, arch->align) != 0)
		return (1);
	return (0);
}

struct fat_arch	*get_archs(struct fat_arch *archs, t_filetype *fat,
size_t nfat_arch)
{
	void				*f_arch;
	uint32_t			i;
	const NXArchInfo	*info;

	i = 0;
	if (!(archs = malloc(sizeof(struct fat_arch) * nfat_arch)))
		return (NULL);
	f_arch = fat->start + sizeof(struct fat_header);
	while (i < nfat_arch)
	{
		archs[i].cputype = swap32(fat->big_endian, ((t_fa*)f_arch)->cputype);
		archs[i].cpusubtype = swap32(fat->big_endian,\
		((t_fa*)f_arch)->cpusubtype);
		archs[i].offset = swap32(fat->big_endian, ((t_fa*)f_arch)->offset);
		archs[i].size = swap32(fat->big_endian, ((t_fa*)f_arch)->size);
		archs[i].align = swap32(fat->big_endian, ((t_fa*)f_arch)->align);
		if (check_oflow(fat, fat->start + archs[i].offset) || ar_ok(&archs[i]))
		{
			free(archs);
			return (NULL);
		}
		f_arch = f_arch + sizeof(t_fa);
		i++;
	}
	return (archs);
}

int				is_macho(uint32_t magic, t_filetype *file)
{
	if (magic == MH_MAGIC_64)
	{
		file->big_endian = FALSE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == MH_CIGAM_64)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == MH_MAGIC)
	{
		file->big_endian = FALSE;
		file->is_64 = FALSE;
		return (1);
	}
	else if (magic == MH_CIGAM)
	{
		file->big_endian = TRUE;
		file->is_64 = FALSE;
		return (1);
	}
	return (0);
}

int				is_fat(uint32_t magic, t_filetype *file)
{
	if (magic == FAT_MAGIC_64)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == FAT_CIGAM_64)
	{
		file->big_endian = FALSE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == FAT_MAGIC)
	{
		file->big_endian = TRUE;
		file->is_64 = FALSE;
		return (1);
	}
	else if (magic == FAT_CIGAM)
	{
		file->big_endian = FALSE;
		file->is_64 = FALSE;
		return (1);
	}
	return (0);
}
#endif

int				is_archive(uint32_t magic, t_filetype *file)
{
	if (ft_strncmp(file->start, ARMAG, SARMAG) == 0)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	#if __MACH__
	else if (magic == OARMAG1)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == OARMAG2)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	#endif
	return (0);
}

#if __linux__
int				is_elf(uint32_t magic, t_filetype *file)
{
	return (ft_memcmp(file->start,ELFMAG, SELFMAG) == 0);
}
#endif