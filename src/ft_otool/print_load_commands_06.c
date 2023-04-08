/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_06.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:32:05 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:32:06 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

#if __MACH__
void	print_prebound_dylib_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian,\
	((struct prebound_dylib_command*)ptr)->name.offset);
	ft_printf("% 13s %s\n", "cmd", info->cmd_name);
	ft_printf("% 13s %"PRIu32"\n", "cmdsize",\
	swap32(big_endian, ((struct prebound_dylib_command*)ptr)->cmdsize));
	ft_printf("% 13s %s (offset %"PRIu32")\n", "name", ptr + offset, offset);
	ft_printf("% 13s %"PRIu32"\n", "nmodules",\
	swap32(big_endian, ((struct prebound_dylib_command*)ptr)->nmodules));
	offset = swap32(big_endian,\
	((struct prebound_dylib_command*)ptr)->linked_modules.offset);
	ft_printf("% 13s %s (offset %"PRIu32")\n",\
	"linked_modules", ptr + offset, offset);
}

void	print_routines_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdsize",\
	swap32(big_endian, ((struct routines_command*)ptr)->cmdsize));
	ft_printf("% 9s 0x%08x\n", "init_address",\
	swap32(big_endian, ((struct routines_command*)ptr)->init_address));
	ft_printf("% 9s 0x%08x\n", "init_module",\
	swap32(big_endian, ((struct routines_command*)ptr)->init_module));
	ft_printf("% 9s %"PRIu32"\n", "reserved1",\
	swap32(big_endian, ((struct routines_command*)ptr)->reserved1));
	ft_printf("% 9s %"PRIu32"\n", "reserved2",\
	swap32(big_endian, ((struct routines_command*)ptr)->reserved2));
	ft_printf("% 9s %"PRIu32"\n", "reserved3",\
	swap32(big_endian, ((struct routines_command*)ptr)->reserved3));
	ft_printf("% 9s %"PRIu32"\n", "reserved4",\
	swap32(big_endian, ((struct routines_command*)ptr)->reserved4));
	ft_printf("% 9s %"PRIu32"\n", "reserved5",\
	swap32(big_endian, ((struct routines_command*)ptr)->reserved5));
	ft_printf("% 9s %"PRIu32"\n", "reserved6",\
	swap32(big_endian, ((struct routines_command*)ptr)->reserved6));
}

void	print_sub_framework_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian,\
	((struct sub_framework_command*)ptr)->umbrella.offset);
	ft_printf("% 13s %s\n", "cmd", info->cmd_name);
	ft_printf("% 13s %"PRIu32"\n", "cmdsize",\
	swap32(big_endian, ((struct routines_command*)ptr)->cmdsize));
	ft_printf("% 13s %s (offset %"PRIu32")\n",\
	"umbrella", ptr + offset, offset);
}

void	print_sub_umbrella_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian,\
	((struct sub_umbrella_command*)ptr)->sub_umbrella.offset);
	ft_printf("% 13s %s\n", "cmd", info->cmd_name);
	ft_printf("% 13s %"PRIu32"\n", "cmdsize",\
	swap32(big_endian, ((struct sub_umbrella_command*)ptr)->cmdsize));
	ft_printf("% 13s %s (offset %"PRIu32")\n",\
	"sub_umbrella", ptr + offset, offset);
}

void	print_sub_client_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian,\
	((struct sub_client_command*)ptr)->client.offset);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdsize",\
	swap32(big_endian, ((struct sub_client_command*)ptr)->cmdsize));
	ft_printf("% 9s %s (offset %"PRIu32")\n",\
	"client", ptr + offset, offset);
}
#endif
