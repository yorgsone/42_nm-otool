/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:27:15 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:27:18 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static void	count_sects(t_filetype *mach, void *start,
int64_t *nsects, t_filetype *file)
{
	void		*load_command;
	uint32_t	ncmds;
	uint32_t	count;

	count = 0;
	load_command = (mach->is_64) ? start + sizeof(struct mach_header_64) :\
	start + sizeof(struct mach_header);
	if (check_oflow(file, load_command))
	{
		*nsects = -1;
		return ;
	}
	ncmds = swap32(mach->big_endian, ((struct mach_header *)start)->ncmds);
	while (ncmds--)
	{
		if (check_oflow(file, load_command))
		{
			*nsects = -1;
			return ;
		}
		count += get_count_sects(mach, load_command);
		load_command += swap32(mach->big_endian, \
		((t_lco*)load_command)->cmdsize);
	}
	*nsects = count;
}

static int	parse_sections(t_filetype *mach, void *start, t_sects *sects)
{
	void		*lc;
	uint32_t	ncmds;
	uint32_t	index;
	uint32_t	cmd;

	if (mach->is_64)
		lc = start + sizeof(struct mach_header_64);
	else
		lc = start + sizeof(struct mach_header);
	if (check_oflow(mach, lc))
		return (-2);
	ncmds = swap32(mach->big_endian, ((struct mach_header *)start)->ncmds);
	while (ncmds--)
	{
		cmd = swap32(mach->big_endian, ((t_lco*)lc)->cmd);
		if (cmd == LC_SEGMENT || cmd == LC_SEGMENT_64)
		{
			index = store_sectname(mach, lc, sects, index);
			if (index == (uint32_t)-1)
				return (-2);
		}
		lc += swap32(mach->big_endian, ((t_lco*)lc)->cmdsize);
	}
	return (1);
}

static void	del(void *content, size_t size)
{
	t_symtab_syms	*tmp;

	if (content && size != 0)
	{
		tmp = (t_symtab_syms *)content;
		if (tmp->name)
			free(tmp->name);
		free(content);
	}
}

static int	inner_mach_o(t_sects *sects, int argc,
t_filetype *mach, t_filetype *file)
{
	t_list	*syms;

	if (!(syms = ft_lstnew(NULL, 0)))
	{
		sects ? free(sects) : 0;
		return (-1);
	}
	(argc > 2) ? ft_printf("\n%s:\n", mach->name) : 0;
	if (find_symtab(mach, mach->start, &syms, file) != 1)
		return (error_ret(-2, mach->name, NULL));
	if (parse_type(&syms, sects) == -1)
		return (-1);
	ft_lstsort(syms, sort_mysyms_alpha);
	print_syms(mach, &syms);
	ft_lstdel(&syms, del);
	return (1);
}

int			handle_mach_o(int argc, t_filetype *mach, t_filetype *file)
{
	t_list	*syms;
	t_sects	*sects;
	int64_t	nsects;
	int		ret;

	if (check_oflow(file, mach->start + sizeof(uint32_t)))
		return (error_ret(-2, mach->name, NULL));
	count_sects(mach, mach->start, &nsects, file);
	if (nsects < 0)
		return (error_ret(-2, mach->name, NULL));
	if (!(sects = (t_sects *)malloc(sizeof(t_sects) * nsects)))
		return (-1);
	if (parse_sections(mach, mach->start, sects) != 1)
		return (error_ret(-2, mach->name, NULL));
	ret = inner_mach_o(sects, argc, mach, file);
	if (ret == -2)
		return (error_ret(-2, mach->name, NULL));
	else if (ret == -1)
		return (-1);
	if (sects)
		free(sects);
	return (1);
}
