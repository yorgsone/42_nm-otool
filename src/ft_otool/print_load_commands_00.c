/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_00.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:31:09 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:14 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

static void	print_section_64_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 9s %" PRIu32 "\n", "reserved1",
		swap32(big_endian, ((t_s64 *)ptr)->reserved1));
	ft_printf("% 9s %" PRIu32 "\n", "reserved2",
		swap32(big_endian, ((t_s64 *)ptr)->reserved2));
	ft_printf("% 9s %" PRIu32 "\n", "reserved3",
		swap32(big_endian, ((t_s64 *)ptr)->reserved3));
}

static void	print_section_64(void *ptr, uint32_t nsects, uint8_t big_endian)
{
	uint32_t align;

	while (nsects--)
	{
		ft_printf("Section\n");
		ft_printf("% 9s %s\n", "sectname", ((t_s64*)ptr)->sectname);
		ft_printf("% 9s %s\n", "segname", ((t_s64*)ptr)->segname);
		ft_printf("% 9s 0x%016llx\n", "addr",\
		swap64(big_endian, ((t_s64*)ptr)->addr));
		ft_printf("% 9s 0x%016x\n", "size",\
		swap64(big_endian, ((t_s64*)ptr)->size));
		ft_printf("% 9s %" PRIu32 "\n", "offset",\
		swap32(big_endian, ((t_s64*)ptr)->offset));
		align = swap32(big_endian, ((t_s64*)ptr)->align);
		ft_printf("% 9s 2^%" PRIu32 " (%d)\n",\
		"align", align, ft_pow2(2, align));
		ft_printf("% 9s %" PRIu32 "\n", "reloff",\
		swap32(big_endian, ((t_s64*)ptr)->reloff));
		ft_printf("% 9s %" PRIu32 "\n", "nreloc",\
		swap32(big_endian, ((t_s64*)ptr)->nreloc));
		ft_printf("% 9s 0x%08x\n", "flags",\
		swap32(big_endian, ((t_s64*)ptr)->flags));
		ptr = ptr + sizeof(t_s64);
	}
}

static void	print_sc64_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 9s 0x%016llx\n", "vmaddr",\
	swap64(big_endian, ((struct segment_command_64*)ptr)->vmaddr));
	ft_printf("% 9s 0x%016llx\n", "vmsize",\
	swap64(big_endian, ((struct segment_command_64*)ptr)->vmsize));
	ft_printf("% 9s %"PRIu64"\n", "fileoff",\
	swap64(big_endian, ((struct segment_command_64*)ptr)->fileoff));
	ft_printf("% 9s %"PRIu64"\n", "filesize",\
	swap64(big_endian, ((struct segment_command_64*)ptr)->filesize));
	ft_printf("% 9s 0x%08x\n", "maxprot",\
	swap64(big_endian, ((struct segment_command_64*)ptr)->maxprot));
	ft_printf("% 9s 0x%08x\n", "initprot",\
	swap64(big_endian, ((struct segment_command_64*)ptr)->initprot));
}

void		print_sc64(void *com, const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	nsects;

	nsects = 0;
	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside", swap32(big_endian,\
	((struct segment_command_64*)ptr)->cmdsize));
	ft_printf("% 9s %s\n", "segname",\
	((struct segment_command_64*)ptr)->segname);
	print_sc64_2(ptr, big_endian);
	nsects = swap32(big_endian, ((struct segment_command_64*)ptr)->nsects);
	ft_printf("% 9s %"PRIu32"\n", "nsects", nsects);
	ft_printf("% 9s 0x%x\n", "flags",\
	swap32(big_endian, ((struct segment_command_64*)ptr)->flags));
	ptr = com + sizeof(struct segment_command_64);
	print_section_64(ptr, nsects, big_endian);
}
