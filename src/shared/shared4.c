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

static int		check_arch_errors(int cputype, int cpusubtype,
uint32_t offset, uint32_t align)
{
	if ((cputype == 0 && cpusubtype == 0) \
		|| offset == 0 || offset % ft_pow2(2, align) != 0)
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
		info = NXGetArchInfoFromCpuType(archs[i].cputype, archs[i].cpusubtype);
		archs[i].offset = swap32(fat->big_endian, ((t_fa*)f_arch)->offset);
		archs[i].size = swap32(fat->big_endian, ((t_fa*)f_arch)->size);
		archs[i].align = swap32(fat->big_endian, ((t_fa*)f_arch)->align);
		if (check_oflow(fat, fat->start + archs[i].offset) ||\
		check_arch_errors(archs[i].cputype, archs[i].cpusubtype,\
		archs[i].offset, archs[i].align))
			return (NULL);
		f_arch = f_arch + sizeof(t_fa);
		i++;
	}
	return (archs);
}

int				is_macho(uint32_t magic, t_filetype *file)
{
	if (magic == MH_MAGIC_64)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == MH_CIGAM_64)
	{
		file->big_endian = FALSE;
		file->is_64 = TRUE;
		return (1);
	}
	else if (magic == MH_MAGIC)
	{
		file->big_endian = TRUE;
		file->is_64 = FALSE;
		return (1);
	}
	else if (magic == MH_CIGAM)
	{
		file->big_endian = FALSE;
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

int				is_archive(uint32_t magic, t_filetype *file)
{
	if (magic == OARMAG1)
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
	else if (ft_strncmp(file->start, ARMAG, SARMAG) == 0)
	{
		file->big_endian = TRUE;
		file->is_64 = TRUE;
		return (1);
	}
	return (0);
}
