/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:26:19 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:26:32 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

uint32_t	get_count_sects(t_filetype *mach, void *lc)
{
	if (swap32(mach->big_endian, ((t_lco *)lc)->cmd) == LC_SEGMENT)
		return (swap32(mach->big_endian, ((t_sc *)lc)->nsects));
	else if (swap32(mach->big_endian, ((t_lco *)lc)->cmd) == LC_SEGMENT_64)
		return (swap32(mach->big_endian, ((t_sc64 *)lc)->nsects));
	else
		return (0);
}

int			find_symtab(t_filetype *mach, void *start,
t_list **my_syms, t_filetype *file)
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
		if (check_oflow(file, load_command) ||\
		check_lc_errors((t_lco*)load_command, mach) == -1)
			return (-1);
		if (swap32(mach->big_endian, ((t_lco*)load_command)->cmd) \
		== LC_SYMTAB)
			if (parse_symtab_command(mach, load_command, my_syms, file) != 1)
				return (-1);
		load_command += swap32(mach->big_endian,\
		((t_lco*)load_command)->cmdsize);
		i++;
	}
	return (1);
}

int			parse_symtab_command(t_filetype *mach, void *load_command,
t_list **my_syms, t_filetype *file)
{
	void	*ptr;

	ptr = load_command;
	if (mach->is_64)
	{
		if (save_syms_64(ptr, my_syms, mach, file) != 1)
			return (-1);
	}
	else
	{
		if (save_syms_32(ptr, my_syms, mach, file) != 1)
			return (-1);
	}
	return (1);
}

void		inner_print_sym(int select, int pad_size, t_symtab_syms *sym)
{
	if (select == 1)
		ft_printf("%*s %c %s\n", pad_size, " ",\
		sym->type, sym->name);
	else if (select == 2)
		ft_printf("%0*llx %c %s\n",\
		pad_size, sym->n_value, sym->type, sym->name);
	else
		ft_printf("%0*x %c %s\n", \
		pad_size, (uint32_t)sym->n_value, sym->type, sym->name);
}

void		print_syms(t_filetype *mach, t_list **syms)
{
	int				pad_size;
	t_list			*sym;
	t_symtab_syms	*tmp;

	sym = *syms;
	while (sym->content && sym->next)
	{
		tmp = (t_symtab_syms *)sym->content;
		if (tmp->type != '-')
		{
			pad_size = (mach->is_64) ? 16 : 8;
			if (tmp->name)
			{
				if (tmp->n_value == 0 && (tmp->type == 'U' || tmp->type == 'u'))
					inner_print_sym(1, pad_size, tmp);
				else if (mach->is_64)
					inner_print_sym(2, pad_size, tmp);
				else
					inner_print_sym(3, pad_size, tmp);
			}
		}
		sym = sym->next;
	}
}
