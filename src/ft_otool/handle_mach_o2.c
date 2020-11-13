/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mach_o2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:30:59 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:31:01 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

int	save_syms_32(void *ptr, t_filetype *mach, t_filetype *file)
{
	void			*strtab;
	void			*symtab;
	uint32_t		nsyms;
	char			*symname;
	struct nlist	*symbols_d;

	symname = NULL;
	strtab = mach->start + swap32(mach->big_endian,
		((struct symtab_command *)ptr)->stroff);
	symtab = mach->start + swap32(mach->big_endian,
		((struct symtab_command *)ptr)->symoff);
	if (check_oflow(file, strtab) || check_oflow(file, symtab))
		return (-1);
	nsyms = swap32(mach->big_endian, ((struct symtab_command *)ptr)->nsyms);
	while (nsyms--)
	{
		symbols_d = (struct nlist *)symtab + nsyms;
		symname = strtab + swap32(mach->big_endian, symbols_d->n_un.n_strx);
		symbols_d += sizeof(struct nlist);
	}
	return (1);
}

int	save_syms_64(void *ptr, t_filetype *mach, t_filetype *file)
{
	void			*strtab;
	void			*symtab;
	char			*symname;
	uint32_t		nsyms;
	struct nlist_64	*symbols_d64;

	symname = NULL;
	strtab = mach->start + swap32(mach->big_endian,
		((struct symtab_command *)ptr)->stroff);
	symtab = mach->start + swap32(mach->big_endian,
		((struct symtab_command *)ptr)->symoff);
	if (check_oflow(file, strtab) || check_oflow(file, symtab))
		return (-1);
	nsyms = swap32(mach->big_endian, ((struct symtab_command *)ptr)->nsyms);
	while (nsyms--)
	{
		symbols_d64 = (struct nlist_64 *)symtab + nsyms;
		symname = strtab + swap64(mach->big_endian,
			symbols_d64->n_un.n_strx);
		symbols_d64 += sizeof(struct nlist_64);
	}
	return (1);
}

int	parse_symtab_command(t_filetype *mach, void *load_command,
	t_filetype *file)
{
	void *ptr;

	ptr = load_command;
	if (mach->is_64)
	{
		if (save_syms_64(ptr, mach, file) != 1)
			return (-1);
	}
	else
	{
		if (save_syms_32(ptr, mach, file) != 1)
			return (-1);
	}
	return (1);
}

int	find_symtab(t_filetype *mach, void *start, t_filetype *file)
{
	void		*load_command;
	uint32_t	ncmds;
	uint32_t	i;

	i = 0;
	if (mach->is_64)
		load_command = start + sizeof(struct mach_header_64);
	else
		load_command = start + sizeof(struct mach_header);
	ncmds = swap32(mach->big_endian, ((struct mach_header *)start)->ncmds);
	while (i < ncmds)
	{
		if (check_oflow(file, load_command) ||
		check_lc_errors(load_command, mach) == -1)
			return (-1);
		if (swap32(mach->big_endian, ((t_lco *)load_command)->cmd) == LC_SYMTAB)
			if (parse_symtab_command(mach, load_command, file) != 1)
				return (-1);
		load_command += swap32(mach->big_endian,
			((t_lco *)load_command)->cmdsize);
		i++;
	}
	return (1);
}
