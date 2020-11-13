/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_09.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:32:24 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:32:27 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

void	print_version_min_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	version;
	uint32_t	sdk;

	ptr = com;
	version = swap32(big_endian, ((struct version_min_command*)ptr)->version);
	sdk = swap32(big_endian, ((struct version_min_command*)ptr)->sdk);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct version_min_command*)ptr)->cmdsize));
	ft_printf("% 9s %u.%u.%u\n", "version", (version & 0xFFFF0000) >> 16,\
	(version & 0x0000FF00) >> 8, (version & 0x000000FF));
	ft_printf("% 9s %u.%u.%u\n", "sdk", (sdk & 0xFFFF0000) >> 16,\
	(sdk & 0x0000FF00) >> 8, (sdk & 0x000000FF));
}

void	print_entry_point_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct entry_point_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "entryoff",\
	swap32(big_endian, ((struct entry_point_command*)ptr)->entryoff));
	ft_printf("% 9s %"PRIu32"\n", "stacksize",\
	swap32(big_endian, ((struct entry_point_command*)ptr)->stacksize));
}

void	print_source_version_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	version;

	ptr = com;
	version = swap32(big_endian,\
	((struct source_version_command*)ptr)->version);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct source_version_command*)ptr)->cmdsize));
	ft_printf("% 9s %u.%u.%u.%u\n", "version", (version & 0xFF000000) >> 24,\
	(version & 0x00FF0000) >> 16,\
	(version & 0x0000FF00) >> 8, (version & 0x000000FF));
}

void	print_encryption_info_command_64(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct encryption_info_command_64*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "cryptoff",\
	swap32(big_endian, ((struct encryption_info_command_64*)ptr)->cryptoff));
	ft_printf("% 9s %"PRIu32"\n", "cryptsize",\
	swap32(big_endian, ((struct encryption_info_command_64*)ptr)->cryptsize));
	ft_printf("% 9s %"PRIu32"\n", "cryptid",\
	swap32(big_endian, ((struct encryption_info_command_64*)ptr)->cryptid));
	ft_printf("% 9s %"PRIu32"\n", "pad",\
	swap32(big_endian, ((struct encryption_info_command_64*)ptr)->pad));
}
