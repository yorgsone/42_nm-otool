/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:33:21 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:33:23 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

extern int	g_optind;
extern int	g_optcol;
extern int	g_optopt;
extern int	g_opterr;

uint8_t			parse_opt(int ar, char **ag, uint8_t flags)
{
	int opt;

	opt = -1;
	while ((opt = ft_getopt(ar, ag, "fahlt")) > -1)
	{
		if (opt == 'f')
			flags |= FLAG_F;
		else if (opt == 'a')
			flags |= FLAG_A;
		else if (opt == 'h')
			flags |= FLAG_H;
		else if (opt == 'l')
			flags |= FLAG_L;
		else if (opt == 't')
			flags |= FLAG_T;
	}
	if (opt == E_INVALID_OPT)
		exit(opt);
	return (flags);
}

static int8_t	handle_file(uint32_t magic_number, t_filetype *file,
uint8_t flags)
{
	if (is_macho(magic_number, file))
		handle_mach_o(file, flags, file);
	else if (is_fat(magic_number, file))
		handle_fat(file, flags);
	else if (is_archive(magic_number, file))
		handle_ar(file, flags);
	else
	{
		error(file->name, "The file was not recognized as a valid object file");
		return (-1);
	}
	return (1);
}

static int		ft_otool(uint8_t flags, char *name)
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
		error(name, "Could not map file");
		close(fd);
		return (-1);
	}
	file.size = size;
	file.end = file.start + file.size;
	handle_file(*(uint32_t *)file.start, &file, flags);
	munmap(file.start, size);
	close(fd);
	return (1);
}

int				main(int ar, char **ag)
{
	uint8_t	flags;

	if (ar >= 3)
	{
		if (*ag[1] != '-')
		{
			ft_printf("Usage: ./otool [-fahlt] <object file> <...>\n");
			return (-1);
		}
		flags = parse_opt(ar, ag, 0b0);
		if (g_opterr == E_EOF)
		{
			ft_printf("Usage: ./otool [-fahlt] <object file> <...>\n");
			return (-1);
		}
		while (g_optind < ar)
		{
			ft_otool(flags, ag[g_optind]);
			g_optind++;
		}
	}
	else
		ft_printf("Usage: ./otool [-fahlt] <object file> <...>\n");
	return (0);
}
