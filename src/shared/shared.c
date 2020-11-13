/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:34:03 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:34:04 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shared.h"

void	*o_mmap(int fd, off_t *size)
{
	struct stat buf;

	if (fstat(fd, &buf) < 0)
		return (MAP_FAILED);
	if (buf.st_size == 0)
		return (MAP_FAILED);
	*size = buf.st_size;
	return (mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
}

int		print_macho_header(t_filetype *mach, void *macho_header)
{
	ft_printf("Mach header\n");
	ft_printf("% 11s % 7s % 10s % 5s ", "magic", "cputype", "cpusubtype",\
	"caps");
	ft_printf("% 11s % 6s % 10s % 10s\n", "filetype", "ncmds", "sizeofcmds",\
	"flags");
	ft_printf(" 0x%02x", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->magic));
	ft_printf(" % 7u", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->cputype));
	ft_printf(" % 10u", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->cpusubtype));
	ft_printf("  0x%02x", (swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->cpusubtype) &\
	CPU_SUBTYPE_MASK) >> 24);
	ft_printf(" % 11u", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->filetype));
	ft_printf(" % 6u", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->ncmds));
	ft_printf(" % 10u", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->sizeofcmds));
	ft_printf(" 0x%08x\n", swap32(mach->big_endian,\
	((struct mach_header *)macho_header)->flags));
	return (1);
}

int		is_text_section(t_filetype *mach, void *sect)
{
	if (mach->is_64)
	{
		return ((ft_strcmp(((t_s64*)sect)->segname, "__TEXT") == 0) &&\
		(ft_strcmp(((t_s64*)sect)->sectname, "__text") == 0));
	}
	return ((ft_strcmp(((t_s*)sect)->segname, "__TEXT") == 0) &&\
	(ft_strcmp(((t_s*)sect)->sectname, "__text") == 0));
}

void	ft_hexdump_line_values(char *start, int64_t len, t_filetype *file)
{
	int64_t i;

	i = 0;
	while (i < len)
	{
		if (!file->big_endian)
		{
			if (i + 3 - 2 * (i % 4) < len)
			{
				ft_printf("%02x", (uint8_t)start[i + 3 - 2 * (i % 4)]);
				if (i % 4 == 3 && file->is_64)
					ft_printf(" ");
				else
					ft_printf(" ");
			}
		}
		else
			ft_printf("%02x ", (uint8_t)start[i]);
		i++;
	}
}

void	ft_hexdump(void *start, int64_t size,
int64_t start_address, t_filetype *file)
{
	int64_t	len;

	len = size > 16 ? 16 : size;
	while (len > 0)
	{
		ft_printf("%0*llx%s", (!file->is_64)
			? 8 : 16, start_address, "\t");
		ft_hexdump_line_values(start, len, file);
		ft_printf("\n");
		start += 16;
		start_address += 16;
		size -= 16;
		len = size > 16 ? 16 : size;
	}
}
