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

int			check_error(t_filetype *mach, t_filetype *file)
{
	if (find_symtab(mach, mach->start, file) != 1)
		return (-1);
	return (1);
}

void		print_load_command(void *lco, t_filetype *mach)
{
	const t_lc *lc;

	lc = lc_info_from_id(swap32(mach->big_endian, ((t_lco *)lco)->cmd));
	if (lc->print_seg)
		lc->print_seg(lco, lc, mach->big_endian);
}

int			print_long_mach_o(t_filetype *mach, uint8_t flags, t_filetype *file)
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

int			handle_mach_o(t_filetype *mach, uint8_t flags, t_filetype *file)
{
	if (check_oflow(file, mach->start + sizeof(uint32_t)))
		return (error_ret(-2, mach->name, NULL));
	if (check_error(mach, file) == -1)
		return (error_ret(-2, mach->name, NULL));
	if (chk_flag(FLAG_L, flags) || chk_flag(FLAG_T, flags))
	{
		ft_printf("%s:\n", mach->name);
		if (print_long_mach_o(mach, flags, mach) != 1)
			error_ret(-2, mach->name, NULL);
	}
	else if (chk_flag(FLAG_H, flags))
		print_macho_header(mach, mach->start);
	return (1);
}
