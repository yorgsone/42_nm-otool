/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_05.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:31:55 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:58 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

static void	print_time(uint32_t timestamp)
{
	time_t		t;
	struct tm	*timeinfo;

	t = timestamp;
	timeinfo = localtime(&t);
	ft_printf("% 13s %u %s", "timestamp", timestamp, asctime(timeinfo));
}

static void	print_dylib_struct(void *ptr, uint8_t big_endian)
{
	uint32_t	offset;
	uint32_t	timestamp;
	uint32_t	cur_version;
	uint32_t	comp_version;

	offset = swap32(big_endian,\
	((struct dylib_command*)ptr)->dylib.name.offset);
	timestamp = swap32(big_endian,\
	((struct dylib_command*)ptr)->dylib.timestamp);
	cur_version = swap32(big_endian,\
	((struct dylib_command*)ptr)->dylib.current_version);
	comp_version = swap32(big_endian,\
	((struct dylib_command*)ptr)->dylib.compatibility_version);
	ft_printf("% 13s %s (offset %"PRIu32")\n", "name", ptr + offset, offset);
	print_time(timestamp);
	ft_printf("% 21s %u.%u.%u\n", "current version",\
	(cur_version & 0xFFFF0000) >> 16,\
	(cur_version & 0x0000FF00) >> 8, (cur_version & 0x000000FF));
	ft_printf("% 21s %u.%u.%u\n", "compatibility version",\
	(comp_version & 0xFFFF0000) >> 16, \
	(comp_version & 0x0000FF00) >> 8, (comp_version & 0x000000FF));
}

void		print_dylib_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 13s %s\n", "cmd", info->cmd_name);
	ft_printf("% 13s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct dylib_command*)ptr)->cmdsize));
	print_dylib_struct(ptr, big_endian);
}

void		print_dylinker_command(void *com, const t_lc *info,
			uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian, ((struct dylinker_command*)ptr)->name.offset);
	ft_printf("% 13s %s\n", "cmd", info->cmd_name);
	ft_printf("% 13s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct dylinker_command*)ptr)->cmdsize));
	ft_printf("% 13s %s (offset %"PRIu32")\n", "name", ptr + offset, offset);
}
