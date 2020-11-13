/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:34:17 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:34:19 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shared.h"

static int64_t	get_value(void *sect, t_filetype *mach, char c)
{
	if (mach->is_64)
	{
		if (c == 'a')
			return (swap64(mach->big_endian, ((t_s64*)sect)->addr));
		else if (c == 's')
			return (swap64(mach->big_endian, ((t_s64*)sect)->size));
		else if (c == 'o')
		{
			return (swap64(mach->big_endian,\
				(int64_t)((t_s64*)sect)->offset));
		}
		return (0);
	}
	if (c == 'a')
		return (swap32(mach->big_endian, (int64_t)((t_s*)sect)->addr));
	else if (c == 's')
		return (swap32(mach->big_endian, (int64_t)((t_s*)sect)->size));
	else if (c == 'o')
		return (swap32(mach->big_endian, (int64_t)((t_s*)sect)->offset));
	return (0);
}

static int		inner_t_option(t_filetype *mach, void *ptr, void *start)
{
	void		*sect;
	uint32_t	nsects;
	uint32_t	segment_size;
	uint32_t	section_size;

	segment_size = (mach->is_64) ? sizeof(t_sc64) : sizeof(t_sc);
	section_size = (mach->is_64) ? sizeof(t_s64) : sizeof(t_s);
	nsects = (mach->is_64) ? swap32(mach->big_endian,\
	((t_sc64*)ptr)->nsects) : swap32(mach->big_endian, ((t_sc*)ptr)->nsects);
	sect = ptr + segment_size;
	if (check_oflow(mach, sect))
		return (-1);
	if (check_oflow(mach, sect + section_size))
		return (-1);
	while (nsects--)
	{
		if (is_text_section(mach, sect))
		{
			ft_printf("Contents of (__TEXT,__text) section\n");
			ft_hexdump(start + get_value(sect, mach, 'o'),\
			get_value(sect, mach, 's'), get_value(sect, mach, 'a'), mach);
		}
		sect += section_size;
	}
	return (1);
}

int				check_lc_errors(struct load_command *lc, t_filetype *mach)
{
	void		*endofcmds;
	uint64_t	cmd_size;

	cmd_size = lc->cmdsize;
	endofcmds = (struct load_command *)(mach->start + ((!mach->is_64) ?
		sizeof(struct mach_header) :\
		sizeof(struct mach_header_64))) + swap32(mach->big_endian,
		(!mach->is_64) ? ((struct mach_header *)(mach->start))->sizeofcmds
		: ((struct mach_header_64 *)(mach->start))->sizeofcmds);
	if ((void *)lc + (cmd_size || 1) > endofcmds)
		return (-1);
	return (1);
}

void			t_option(void *start, t_filetype *mach,
void *segment_command, uint32_t ncmds)
{
	void		*ptr;
	uint32_t	i;
	uint32_t	cmd;

	ptr = segment_command;
	cmd = swap32(mach->big_endian, ((struct load_command *)ptr)->cmd);
	i = 0;
	while (i < ncmds)
	{
		if (cmd == LC_SEGMENT_64 || cmd == LC_SEGMENT)
			inner_t_option(mach, ptr, start);
		ptr += swap32(mach->big_endian, ((struct load_command *)ptr)->cmdsize);
		cmd = swap32(mach->big_endian, ((struct load_command *)ptr)->cmd);
		i++;
	}
}

int				check_oflow(t_filetype *file, void *ptr)
{
	if ((ptr > file->start + file->size)
		|| (ptr > file->end) || (ptr < file->start))
		return (1);
	return (0);
}
