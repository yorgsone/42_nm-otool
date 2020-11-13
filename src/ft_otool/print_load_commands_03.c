/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_load_commands_03.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:31:36 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:40 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

void	print_symtab_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 8s %s\n", "cmd", info->cmd_name);
	ft_printf("% 8s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct symtab_command*)ptr)->cmdsize));
	ft_printf("% 8s %"PRIu32"\n", "symoff",\
	swap32(big_endian, ((struct symtab_command*)ptr)->symoff));
	ft_printf("% 8s %"PRIu32"\n", "nsyms",\
	swap32(big_endian, ((struct symtab_command*)ptr)->nsyms));
	ft_printf("% 8s %"PRIu32"\n", "stroff",\
	swap32(big_endian, ((struct symtab_command*)ptr)->stroff));
	ft_printf("% 8s %"PRIu32"\n", "strsize",\
	swap32(big_endian, ((struct symtab_command*)ptr)->strsize));
}

void	print_symseg_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct symseg_command*)ptr)->cmdsize));
	ft_printf("% 9s %"PRIu32"\n", "offset",\
	swap32(big_endian, ((struct symseg_command*)ptr)->offset));
	ft_printf("% 9s %"PRIu32"\n", "size",\
	swap32(big_endian, ((struct symseg_command*)ptr)->size));
}

void	print_thread_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct thread_command*)ptr)->cmdsize));
}

void	print_ident_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void *ptr;

	ptr = com;
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct ident_command*)ptr)->cmdsize));
}

void	print_fvmfile_command(void *com, const t_lc *info, uint8_t big_endian)
{
	void		*ptr;
	uint32_t	offset;

	ptr = com;
	offset = swap32(big_endian, ((struct fvmfile_command*)ptr)->name.offset);
	ft_printf("% 9s %s\n", "cmd", info->cmd_name);
	ft_printf("% 9s %"PRIu32"\n", "cmdside",\
	swap32(big_endian, ((struct fvmfile_command*)ptr)->cmdsize));
	ft_printf("% 9s %s (offset %"PRIu32")\n", "name", ptr + offset, offset);
	ft_printf("% 9s 0x%016x\n", "header_addr",\
	swap32(big_endian, ((struct fvmfile_command*)ptr)->header_addr));
}
