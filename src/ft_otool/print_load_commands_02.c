/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:31:26 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:31 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

#if __MACH__
static void	print_section_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 9s %" PRIu32 "\n", "reloff",\
	swap32(big_endian, ((struct section *)ptr)->reloff));
	ft_printf("% 9s %" PRIu32 "\n", "nreloc",\
	swap32(big_endian, ((struct section *)ptr)->nreloc));
	ft_printf("% 9s 0x%08x\n", "flags",\
	swap32(big_endian, ((struct section *)ptr)->flags));
	ft_printf("% 9s %" PRIu32 "\n", "reserved1",\
	swap32(big_endian, ((struct section *)ptr)->reserved1));
	ft_printf("% 9s %" PRIu32 "\n", "reserved2",\
	swap32(big_endian, ((struct section *)ptr)->reserved2));
}

static void	print_section(void *ptr, uint32_t nsects, uint8_t big_endian)
{
	uint32_t	align;

	while (nsects--)
	{
		ft_printf("Section\n");
		ft_printf("% 9s %s\n", "sectname", ((struct section *)ptr)->sectname);
		ft_printf("% 9s %s\n", "segname", ((struct section *)ptr)->segname);
		ft_printf("% 9s 0x%016llx\n", "addr",\
		swap32(big_endian, ((struct section *)ptr)->addr));
		ft_printf("% 9s 0x%016x\n", "size",\
		swap32(big_endian, ((struct section *)ptr)->size));
		ft_printf("% 9s %" PRIu32 "\n", "offset",\
		swap32(big_endian, ((struct section *)ptr)->offset));
		print_section_2(ptr, big_endian);
		align = swap32(big_endian, ((struct section *)ptr)->align);
		ft_printf("% 9s 2^%" PRIu32 " (%d)\n",\
		"align", align, ft_pow2(2, align));
		ptr = ptr + sizeof(struct section);
	}
}

static void	print_sc_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 9s %"PRIu32"\n", "fileoff",\
	swap32(big_endian, ((struct segment_command*)ptr)->fileoff));
	ft_printf("% 9s %"PRIu32"\n", "filesize",\
	swap32(big_endian, ((struct segment_command*)ptr)->filesize));
	ft_printf("% 9s 0x%08x\n", "maxprot",\
	swap32(big_endian, ((struct segment_command*)ptr)->maxprot));
	ft_printf("% 9s 0x%08x\n", "initprot",\
	swap32(big_endian, ((struct segment_command*)ptr)->initprot));
}

void		print_sc(void *com, const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	nsects;

	nsects = 0;
	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdsize",\
	swap32(big_endian, ((struct segment_command*)ptr)->cmdsize));
	ft_printf("% 9s %s\n", "segname", ((struct segment_command*)ptr)->segname);
	ft_printf("% 9s 0x%08x\n", "vmaddr",\
	swap32(big_endian, ((struct segment_command*)ptr)->vmaddr));
	ft_printf("% 9s 0x%08x\n", "vmsize",\
	swap32(big_endian, ((struct segment_command*)ptr)->vmsize));
	print_sc_2(ptr, big_endian);
	nsects = swap32(big_endian, ((struct segment_command*)ptr)->nsects);
	ft_printf("% 9s %"PRIu32"\n", "nsects", nsects);
	ft_printf("% 9s 0x%x\n", "flags",\
	swap32(big_endian, ((struct segment_command*)ptr)->flags));
	ptr = com + sizeof(struct segment_command);
	print_section(ptr, nsects, big_endian);
}
#endif
