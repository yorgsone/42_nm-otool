/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:28:10 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:30:15 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

int		save_syms_64(void *ptr, t_list **my_syms,
t_filetype *mach, t_filetype *file)
{
	void			*strtab;
	void			*symtab;
	char			*symname;
	uint32_t		nsyms;
	struct nlist_64	*symbols_d64;

	symname = NULL;
	strtab = mach->start + swap32(mach->big_endian, \
	((struct symtab_command *)ptr)->stroff);
	symtab = mach->start + swap32(mach->big_endian, \
	((struct symtab_command *)ptr)->symoff);
	if (check_oflow(file, strtab) || check_oflow(file, symtab))
		return (-1);
	nsyms = swap32(mach->big_endian, ((struct symtab_command *)ptr)->nsyms);
	while (nsyms--)
	{
		symbols_d64 = (struct nlist_64 *)symtab + nsyms;
		symname = strtab + swap64(mach->big_endian,\
		symbols_d64->n_un.n_strx);
		mach->symname = symname;
		add_sym_64(symbols_d64, my_syms, mach, file);
		symbols_d64 += sizeof(struct nlist_64);
	}
	return (1);
}

int		save_syms_32(void *ptr, t_list **my_syms,
	t_filetype *mach, t_filetype *file)
{
	void			*strtab;
	void			*symtab;
	char			*symname;
	uint32_t		nsyms;
	struct nlist	*symbols_d;

	symname = NULL;
	strtab = mach->start + swap32(mach->big_endian,\
		((struct symtab_command *)ptr)->stroff);
	symtab = mach->start + swap32(mach->big_endian,\
	((struct symtab_command *)ptr)->symoff);
	if (check_oflow(file, strtab) || check_oflow(file, symtab))
		return (-1);
	nsyms = swap32(mach->big_endian, ((struct symtab_command *)ptr)->nsyms);
	while (nsyms--)
	{
		symbols_d = (struct nlist *)symtab + nsyms;
		symname = strtab + swap32(mach->big_endian, symbols_d->n_un.n_strx);
		mach->symname = symname;
		add_sym_32(symbols_d, my_syms, mach, file);
		symbols_d += sizeof(struct nlist);
	}
	return (1);
}

void	add_sym_32(struct nlist *symbols_d, t_list **my_syms,
	t_filetype *mach, t_filetype *file)
{
	t_symtab_syms tmp;

	tmp.n_desc = symbols_d->n_desc;
	tmp.n_type = symbols_d->n_type;
	tmp.n_sect = symbols_d->n_sect;
	tmp.n_value = swap32(mach->big_endian, symbols_d->n_value);
	if (mach->symname)
		tmp.name = ft_strdup_overflow(file, mach->symname, '\n');
	else
		tmp.name = NULL;
	ft_lstadd(my_syms, ft_lstnew((void *)&tmp, sizeof(t_symtab_syms)));
}

void	add_sym_64(struct nlist_64 *symbols_d64, t_list **my_syms,
	t_filetype *mach, t_filetype *file)
{
	t_symtab_syms	tmp;

	tmp.n_desc = symbols_d64->n_desc;
	tmp.n_type = symbols_d64->n_type;
	tmp.n_sect = symbols_d64->n_sect;
	tmp.n_value = swap64(mach->big_endian, symbols_d64->n_value);
	if (mach->symname)
		tmp.name = ft_strdup_overflow(file, mach->symname, '\n');
	else
		tmp.name = NULL;
	ft_lstadd(my_syms, ft_lstnew((void *)&tmp, sizeof(tmp)));
}

char	*ft_strdup_overflow(t_filetype *file, char *src, char end_char)
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (!check_oflow(file, src + size)
		&& src[size] && src[size] != end_char && ft_isprint(src[size]))
		size++;
	if (check_oflow(file, src + size))
		return (ft_strdup("bad string index"));
	if ((str = (char *)malloc(sizeof(*str) * (size + 1 + 1))) == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	if (src[size] == end_char)
		str[i++] = end_char;
	str[i] = 0;
	return (str);
}
