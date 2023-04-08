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

static int	ft_strcmp_e(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (s1[i] && s2[j])
	{
		while (s1[i] && (s1[i] == '_' || s1[i] == '.' || s1[i] == '@'))
			i++;
		while  (s2[j] && (s2[j] == '_' || s2[j] == '.'|| s2[j] == '@'))
			j++;
		if (ft_tolower(s1[i]) != ft_tolower(s2[j]))
			break;
		i++;
		j++;
	}
	return ((unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[j]));
}

int				sort_mysyms_alpha_elf(t_list *lst1, t_list *lst2)
{
	t_symtab_syms *sym1;
	t_symtab_syms *sym2;
	int cmp = 0;

	if (!lst1 || !lst2 || !lst1->content || !lst2->content)
		return (0);
	sym1 = lst1->content;
	sym2 = lst2->content;
	char *a = sym1->name;
	char *b = sym2->name;

	if ((ft_strcmp(a,b)) == 0)
		return 1;
	cmp = ft_strcmp_e(a, b);
	if (cmp == 0)
		if ((cmp = ft_strcmp(a,b)) == 0)
			return (sym1->n_value >= sym2->n_value);
	return (cmp > 0);
}

int				sort_mysyms_alpha(t_list *lst1, t_list *lst2)
{
	t_symtab_syms *sym1;
	t_symtab_syms *sym2;

	if (!lst1 || !lst2 || !lst1->content || !lst2->content)
		return (0);
	sym1 = lst1->content;
	sym2 = lst2->content;
	if (!ft_strcmp(sym1->name, sym2->name))
	{
		return (sym1->n_value >= sym2->n_value);
	}
	return (ft_strcmp(sym1->name, sym2->name) > 0);
}

static int stat_is_regular(const char *file)
{
	struct stat buf;

	if (stat(file, &buf) != 0)
		return (-1);
	return(S_ISREG(buf.st_mode));
}

static int8_t	handle_file(uint32_t magic_number, t_filetype *file, int argc)
{
	#if __linux__
	if (is_elf(magic_number, file))
		handle_elf(magic_number,argc, file);
	#endif
	#if __MACH__
	if (is_macho(magic_number, file))
		handle_mach_o(argc, file, file);
	else if (is_fat(magic_number, file))
		handle_fat(file);
	else if (is_archive(magic_number, file))
		handle_ar(file);
	#endif
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
	int chk = 0;

	init_struct(&file);
	file.name = name;
	if ((chk=stat_is_regular(file.name)) <= 0)
	{
		if (chk == -1)
			ft_printf("ft_nm: '%s': No such file\n", file.name);
		else
			ft_printf("ft_nm: Warning: '%s' is not a regular file\n", file.name);
		return (1);
	}
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		error(name, "Could not open file");
		return (-1);
	}
	if ((file.start = o_mmap(fd, &size)) == MAP_FAILED)
	{
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
