/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_07.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:32:11 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:32:13 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

void	print_sub_library_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian,\
	((struct sub_library_command*)ptr)->sub_library.offset);
	ft_printf("% 11s %s\n", "cmd", info->cmd_name);
	ft_printf("% 11s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct sub_library_command*)ptr)->cmdsize));
	ft_printf("% 11s %s (offset %"PRIu32")\n",\
	"sub_library", ptr + offset, offset);
}

void	print_twolevel_hints_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct twolevel_hints_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "offset",\
	swap32(big_endian, ((struct twolevel_hints_command*)ptr)->offset));
	ft_printf("% 9s %"PRIu32"\n", "nhints",\
	swap32(big_endian, ((struct twolevel_hints_command*)ptr)->nhints));
}

void	print_prebind_cksum_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct prebind_cksum_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "offset",\
	swap32(big_endian, ((struct prebind_cksum_command*)ptr)->cksum));
}

void	print_routines_command_64(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",
	swap32(big_endian, ((struct routines_command_64*)ptr)->cmdsize));
	ft_printf("% 9s 0x%016llx\n", "init_address",\
	swap64(big_endian, ((struct routines_command_64*)ptr)->init_address));
	ft_printf("% 9s 0x%016llx\n", "init_module",\
	swap64(big_endian, ((struct routines_command_64*)ptr)->init_module));
	ft_printf("% 9s %"PRIu32"\n", "reserved1",\
	swap32(big_endian, ((struct routines_command_64*)ptr)->reserved1));
	ft_printf("% 9s %"PRIu32"\n", "reserved2",\
	swap32(big_endian, ((struct routines_command_64*)ptr)->reserved2));
	ft_printf("% 9s %"PRIu32"\n", "reserved3",\
	swap32(big_endian, ((struct routines_command_64*)ptr)->reserved3));
	ft_printf("% 9s %"PRIu32"\n", "reserved4",\
	swap32(big_endian, ((struct routines_command_64*)ptr)->reserved4));
	ft_printf("% 9s %"PRIu32"\n", "reserved5",\
	swap32(big_endian, ((struct routines_command_64*)ptr)->reserved5));
	ft_printf("% 9s %"PRIu32"\n", "reserved6",\
	swap32(big_endian, ((struct routines_command_64*)ptr)->reserved6));
}

void	print_uuid_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	int		i;
	void	*ptr;
	uint8_t	uuid[16];

	ptr = com;
	i = 0;
	ft_memcpy(&uuid, &((struct uuid_command*)ptr)->uuid, 16);
	while (i < 16)
		swap32(big_endian, ((struct uuid_command*)ptr)->uuid[i++]);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct uuid_command*)ptr)->cmdsize));
	ft_printf("% 9s %02X%02X%02X%02X-%02X%02X-%02X%02X", "uuid",\
	uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7]);
	ft_printf("-%02X%02X-%02X%02X%02X%02X%02X%02X\n",\
	uuid[8], uuid[9], uuid[10], uuid[11],\
	uuid[12], uuid[13], uuid[14], uuid[15]);
}
