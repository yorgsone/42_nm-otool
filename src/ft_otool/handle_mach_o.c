/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mach_o.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:33:29 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:33:31 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

#if __MACH__
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
			ft_printf("(__TEXT,__text) section\n");
			ft_hexdump(start + get_value(sect, mach, 'o'),\
			get_value(sect, mach, 's'), get_value(sect, mach, 'a'), mach);
		}
		sect += section_size;
	}
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
	if (!chk_flag(mach->flags, FLAG_L) &&
		chk_flag(mach->flags, FLAG_H))
		print_macho_header(mach, mach->start);
}

int				print_long_mach_o(t_filetype *mach, uint8_t flags,
t_filetype *file)
{
	void		*lco;
	const t_lc	*lc;
	uint32_t	ncmds;
	uint32_t	i;

	lco = (mach->is_64) ? mach->start + sizeof(struct mach_header_64)
						: mach->start + sizeof(struct mach_header);
	if (check_oflow(mach, lco) || check_error(mach, file) == -1)
		return (-1);
	ncmds = swap32(mach->big_endian, ((t_mhdr)mach->start)->ncmds);
	if (chk_flag(FLAG_T, flags))
		t_option(mach->start, mach, lco, ncmds);
	if (chk_flag(FLAG_L, flags))
	{
		print_macho_header(mach, mach->start);
		i = 0;
		while (i < ncmds)
		{
			ft_printf("Load command %d\n", i);
			print_load_command(lco, mach);
			lco += swap32(mach->big_endian, ((t_lco *)lco)->cmdsize);
			i++;
		}
	}
	return (1);
}
#endif

int				handle_mach_o(t_filetype *mach, uint8_t flags, t_filetype *file)
{
	mach->flags = flags;
	if (check_oflow(file, mach->start + sizeof(uint32_t)))
		return (error_ret(-2, mach->name, NULL, NULL));
	if (check_error(mach, file) == -1)
		return (error_ret(-2, mach->name, NULL, NULL));
	if (chk_flag(FLAG_L, flags) || chk_flag(FLAG_T, flags))
	{
		ft_printf("%s:\n", mach->name);
		if (print_long_mach_o(mach, flags, mach) != 1)
			error_ret(-2, mach->name, NULL, NULL);
	}
	else if (chk_flag(FLAG_H, flags))
		print_macho_header(mach, mach->start);
	return (1);
}
