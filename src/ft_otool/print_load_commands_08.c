/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_08.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:32:17 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:32:20 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

void		print_rpath_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian, ((struct rpath_command*)ptr)->path.offset);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct rpath_command*)ptr)->cmdsize));
	ft_printf("% 9s %s (offset %"PRIu32")\n", "path", ptr + offset, offset);
}

void		print_linkedit_data_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct linkedit_data_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "dataoff",\
	swap32(big_endian, ((struct linkedit_data_command*)ptr)->dataoff));
	ft_printf("% 9s %"PRIu32"\n", "datasize", \
	swap32(big_endian, ((struct linkedit_data_command*)ptr)->datasize));
}

void		print_encryption_info_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct encryption_info_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "cryptoff",\
	swap32(big_endian, ((struct encryption_info_command*)ptr)->cryptoff));
	ft_printf("% 9s %"PRIu32"\n", "cryptsize",\
	swap32(big_endian, ((struct encryption_info_command*)ptr)->cryptsize));
	ft_printf("% 9s %"PRIu32"\n", "cryptid",\
	swap32(big_endian, ((struct encryption_info_command*)ptr)->cryptid));
}

static void	print_dyld_info_command_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 15s %"PRIu32"\n", "weak_bind_off",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->weak_bind_off));
	ft_printf("% 15s %"PRIu32"\n", "weak_bind_size",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->weak_bind_size));
	ft_printf("% 15s %"PRIu32"\n", "lazy_bind_off",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->lazy_bind_off));
	ft_printf("% 15s %"PRIu32"\n", "lazy_bind_size",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->lazy_bind_size));
	ft_printf("% 15s %"PRIu32"\n", "export_off",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->export_off));
	ft_printf("% 15s %"PRIu32"\n", "export_size",
	swap32(big_endian, ((struct dyld_info_command*)ptr)->export_size));
}

void		print_dyld_info_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 15s %s\n", "cmd", info->cmd_name);
	ft_printf("% 15s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->cmdsize));
	ft_printf("% 15s %"PRIu32"\n", "rebase_off",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->rebase_off));
	ft_printf("% 15s %"PRIu32"\n", "rebase_size",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->rebase_size));
	ft_printf("% 15s %"PRIu32"\n", "bind_off",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->bind_off));
	ft_printf("% 15s %"PRIu32"\n", "bind_size",\
	swap32(big_endian, ((struct dyld_info_command*)ptr)->bind_size));
	print_dyld_info_command_2(ptr, big_endian);
}
