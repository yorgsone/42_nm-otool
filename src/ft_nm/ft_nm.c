/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:25:37 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:25:38 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

int				sort_mysyms_alpha(t_list *lst1, t_list *lst2)
{
	t_symtab_syms *sym1;
	t_symtab_syms *sym2;

	if (!lst1 || !lst2 || !lst1->content || !lst2->content)
		return (0);
	sym1 = lst1->content;
	sym2 = lst2->content;
	if (!ft_strcmp(sym1->name, sym2->name))
		return (sym1->name >= sym2->name);
	return (ft_strcmp(sym1->name, sym2->name) > 0);
}

static int8_t	handle_file(uint32_t magic_number, t_filetype *file, int argc)
{
	if (is_macho(magic_number, file))
		handle_mach_o(argc, file, file);
	else if (is_fat(magic_number, file))
		handle_fat(file);
	else if (is_archive(magic_number, file))
		handle_ar(file);
	else
	{
		error(file->name, \
		"The file was not recognized as a valid object file");
		return (-1);
	}
	return (1);
}

int				ft_nm(int argc, char *name)
{
	int			fd;
	off_t		size;
	t_filetype	file;

	init_struct(&file);
	file.name = name;
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		error(name, "Could not open file");
		return (-1);
	}
	if ((file.start = o_mmap(fd, &size)) == MAP_FAILED)
	{
		error(name, "Memory mapping failed");
		close(fd);
		return (-1);
	}
	file.size = size;
	file.end = file.start + file.size;
	handle_file(*(uint32_t *)file.start, &file, argc);
	munmap(file.start, size);
	close(fd);
	return (1);
}

int				main(int argc, char **argv)
{
	int i;

	if (argc == 1)
		ft_nm(argc, "a.out");
	else
	{
		i = 1;
		while (i < argc)
		{
			ft_nm(argc, argv[i]);
			i++;
		}
	}
	return (0);
}
