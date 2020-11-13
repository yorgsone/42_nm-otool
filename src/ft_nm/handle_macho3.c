/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:28:38 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:28:40 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

uint32_t	store_sectname(t_filetype *mach, void *section,
t_sects *sects, uint32_t index)
{
	void		*sect;
	size_t		seg_size;
	size_t		sect_size;
	uint32_t	nsect_count;

	sect = section;
	nsect_count = get_nsect_count(mach, section, nsect_count);
	if (nsect_count > 0)
	{
		seg_size = (mach->is_64) ? sizeof(t_sc64) : sizeof(t_sc);
		sect_size = (mach->is_64) ? sizeof(t_s64) : sizeof(t_s);
		sect = sect + seg_size;
		if (check_oflow(mach, sect) || check_oflow(mach, sect + sect_size))
			return (-1);
		while (nsect_count--)
		{
			(mach->is_64) ? \
			ft_strcpy(sects[index].sect_name, ((t_s64*)sect)->sectname) :\
			ft_strcpy(sects[index].sect_name, ((t_s*)sect)->sectname);
			sect = sect + sect_size;
			index++;
		}
	}
	return (index);
}

uint32_t	get_nsect_count(t_filetype *mach, void *segment,
uint32_t nsect_count)
{
	if (mach->is_64)
		return (swap32(mach->big_endian, ((t_sc64 *)segment)->nsects));
	return (swap32(mach->big_endian, ((t_sc *)segment)->nsects));
}

int			parse_type(t_list **syms, t_sects *sects)
{
	t_list	*list;

	list = *syms;
	while (list->next)
	{
		if (list->content)
			assign_type((t_symtab_syms*)list->content, sects);
		else
			return (-1);
		list = list->next;
	}
	return (1);
}

void		assign_type(t_symtab_syms *sym, t_sects *sects)
{
	if (N_STAB & sym->n_type)
		sym->type = '-';
	else if ((N_TYPE & sym->n_type) == N_UNDF)
	{
		if (!sym->name)
			sym->type = 'C';
		else if (N_EXT & sym->n_type)
			sym->type = 'U';
		else
			sym->type = '?';
	}
	else if ((N_TYPE & sym->n_type) == N_SECT)
		sym->type = get_sect_type(sym->n_type, &sects[sym->n_sect - 1]);
	else if ((N_TYPE & sym->n_type) == N_ABS)
		sym->type = 'A';
	else if ((N_TYPE & sym->n_type) == N_INDR)
		sym->type = 'I';
	else
		sym->type = '?';
}

char		get_sect_type(uint8_t n_type, t_sects *sect)
{
	char	ret;

	if (!ft_strcmp(sect->sect_name, SECT_TEXT))
		ret = 'T';
	else if (!ft_strcmp(sect->sect_name, SECT_DATA))
		ret = 'D';
	else if (!ft_strcmp(sect->sect_name, SECT_BSS))
		ret = 'B';
	else
		ret = 'S';
	if (!(n_type & N_EXT))
		ret = ft_tolower(ret);
	return (ret);
}
