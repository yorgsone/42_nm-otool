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

#if __MACH__
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
#endif

int				check_oflow(t_filetype *file, void *ptr)
{
	if ((ptr > file->start + file->size)
		|| (ptr > file->end) || (ptr < file->start))
		return (1);
	return (0);
}
