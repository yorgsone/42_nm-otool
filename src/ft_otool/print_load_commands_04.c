/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_04.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:31:45 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:48 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

static void	print_fvmlib_struct(void *ptr, uint8_t big_endian)
{
	uint32_t offset;

	offset = swap32(big_endian,\
	((struct fvmlib_command*)ptr)->fvmlib.name.offset);
	ft_printf("% 9s %s (offset %"PRIu32")\n", "name", ptr + offset, offset);
	ft_printf("% 9s %"PRIu32"\n", "minor_version",\
	swap32(big_endian, ((struct fvmlib_command*)ptr)->fvmlib.minor_version));
	ft_printf("% 9s 0x%016x\n", "header_addr",\
	swap32(big_endian, ((struct fvmlib_command*)ptr)->fvmlib.header_addr));
}

void		print_fvmlib_command(void *com, const t_lc *info,
			uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct fvmlib_command*)ptr)->cmdsize));
	print_fvmlib_struct(ptr, big_endian);
}

static void	print_dysymtab_command_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 15s %"PRIu32"\n", "modtaboff",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->modtaboff));
	ft_printf("% 15s %"PRIu32"\n", "nmodtab",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nmodtab));
	ft_printf("% 15s %"PRIu32"\n", "extrefsymoff",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->extrefsymoff));
	ft_printf("% 15s %"PRIu32"\n", "nextrefsyms",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nextrefsyms));
	ft_printf("% 15s %"PRIu32"\n", "indirectsymoff",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->indirectsymoff));
	ft_printf("% 15s %"PRIu32"\n", "nindirectsyms",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nindirectsyms));
	ft_printf("% 15s %"PRIu32"\n", "extreloff",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->extreloff));
	ft_printf("% 15s %"PRIu32"\n", "nextrel",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nextrel));
	ft_printf("% 15s %"PRIu32"\n", "locreloff",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->locreloff));
	ft_printf("% 15s %"PRIu32"\n", "nlocrel",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nlocrel));
}

void		print_dysymtab_command(void *com, const t_lc *info,
			uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 15s %s\n", "cmd", info->cmd_name);
	ft_printf("% 15s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->cmdsize));
	ft_printf("% 15s %"PRIu32"\n", "ilocalsym",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->ilocalsym));
	ft_printf("% 15s %"PRIu32"\n", "nlocalsym",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nlocalsym));
	ft_printf("% 15s %"PRIu32"\n", "iextdefsym",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->iextdefsym));
	ft_printf("% 15s %"PRIu32"\n", "nextdefsym",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nextdefsym));
	ft_printf("% 15s %"PRIu32"\n", "iundefsym",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->iundefsym));
	ft_printf("% 15s %"PRIu32"\n", "nundefsym",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->nundefsym));
	ft_printf("% 15s %"PRIu32"\n", "tocoff",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->tocoff));
	ft_printf("% 15s %"PRIu32"\n", "ntoc",\
	swap32(big_endian, ((struct dysymtab_command*)ptr)->ntoc));
	print_dysymtab_command_2(ptr, big_endian);
}
