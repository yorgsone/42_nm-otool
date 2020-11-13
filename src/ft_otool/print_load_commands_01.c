/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:31:19 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:21 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

void		print_note_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct note_command*)ptr)->cmdsize));
	ft_printf("% 9s %s\n", "data_owner",\
	((struct note_command*)ptr)->data_owner);
	ft_printf("% 9s %"PRIu32"\n", "offset",\
	swap32(big_endian, ((struct note_command*)ptr)->offset));
	ft_printf("% 9s %"PRIu32"\n", "size",\
	swap32(big_endian, ((struct note_command*)ptr)->size));
}

void		print_linker_option_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct linker_option_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "count",\
	swap32(big_endian, ((struct linker_option_command*)ptr)->count));
}

static void	print_build_version_command_2(void *ptr, uint8_t big_endian)
{
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct build_version_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "platform",\
	swap32(big_endian, ((struct build_version_command*)ptr)->platform));
}

void		print_build_version_command(void *com,
const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	minos;
	uint32_t	sdk;
	uint32_t	tool_version;

	ptr = com;
	minos = swap32(big_endian, ((struct build_version_command*)ptr)->minos);
	sdk = swap32(big_endian, ((struct build_version_command*)ptr)->sdk);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	print_build_version_command_2(ptr, big_endian);
	ft_printf("% 9s %u.%u.%u\n", "minos", (minos & 0xFFFF0000) >> 16,\
	(minos & 0x0000FF00) >> 8, (minos & 0x000000FF));
	ft_printf("% 9s %u.%u.%u\n", "sdk", (sdk & 0xFFFF0000) >> 16,\
	(sdk & 0x0000FF00) >> 8, (sdk & 0x000000FF));
	ft_printf("% 9s %"PRIu32"\n", "ntools", swap32(big_endian,\
	((struct build_version_command*)ptr)->ntools));
	ptr = ptr + sizeof(struct build_version_command);
	tool_version = swap32(big_endian,\
	((struct build_tool_version*)ptr)->version);
	ft_printf("% 9s %"PRIu32"\n", "tool", swap32(big_endian,\
	((struct build_tool_version*)ptr)->tool));
	ft_printf("% 9s %u.%u.%u\n", "version", (tool_version & 0xFFFF0000) >> 16,\
	(tool_version & 0x0000FF00) >> 8, (tool_version & 0x000000FF));
}
