/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:34:10 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:34:13 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shared.h"

void				init_struct(t_filetype *file)
{
	file->big_endian = -1;
	file->magic = 0;
	file->name = NULL;
	file->start = NULL;
	file->end = NULL;
	file->is_64 = -1;
	file->size = 0;
	file->flags = 0;
}

int					error_ret(int err_code, const char *err_file,
const char *err_msg)
{
	if (err_code == -2)
	{
		ft_printf("error: %s truncated or malformed file\n\n", err_file);
		return (err_code);
	}
	else if (err_code == -3)
	{
		if (!err_msg)
			ft_printf("error: %s %s\n\n", err_file, "Unknown error");
		else
			ft_printf("error: %s %s\n\n", err_file, err_msg);
		return (err_code);
	}
	else
	{
		ft_printf("error: %s malloc error\n\n", err_file);
		return (-1);
	}
}

void				error(char *at, char *error)
{
	ft_printf("error: %s: %s\n\n", at, error);
}

void				free_nxinfo(const NXArchInfo *o1, const NXArchInfo *o2)
{
	if (o1)
		NXFreeArchInfo(o1);
	if (o2)
		NXFreeArchInfo(o2);
}

const NXArchInfo	*get_local_arch(struct fat_arch *fat_archs,
uint32_t nfat_arch, const NXArchInfo *local_arch, const NXArchInfo *from_name)
{
	struct fat_arch	*chosen;

	chosen = NULL;
	local_arch = NXGetLocalArchInfo();
	if (local_arch)
		from_name = NXGetArchInfoFromName(local_arch->name);
	if (from_name)
		chosen = NXFindBestFatArch(from_name->cputype, from_name->cpusubtype,\
		fat_archs, nfat_arch);
	if (chosen)
	{
		while (nfat_arch--)
		{
			if (fat_archs[nfat_arch].cputype == chosen->cputype &&\
			fat_archs[nfat_arch].cpusubtype == chosen->cpusubtype)
			{
				free_nxinfo(from_name, local_arch);
				return (NXGetArchInfoFromCpuType(chosen->cputype,\
				chosen->cpusubtype));
			}
		}
	}
	free_nxinfo(from_name, local_arch);
	return (NULL);
}
