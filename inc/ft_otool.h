/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:20:45 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:20:48 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "shared.h"
# include "ft_getopt.h"
# include "loading_command_name.h"

# define FLAG_F         1
# define FLAG_A         2
# define FLAG_H         4
# define FLAG_L         8
# define FLAG_T         16

int		handle_fat(t_filetype *fat, uint8_t flags);
int		handle_mach_o(t_filetype *mach, uint8_t flags, t_filetype *file);
int		print_long_mach_o(t_filetype *mach, uint8_t flags, t_filetype *file);
int		check_error(t_filetype *mach, t_filetype *file);
int		chk_flag(int flags, int check);
int		find_symtab(t_filetype *mach, void *start, t_filetype *file);
int		parse_symtab_command(t_filetype *mach, void *load_command,
		t_filetype *file);
int		save_syms_32(void *ptr, t_filetype *mach, t_filetype *file);
int		save_syms_64(void *ptr, t_filetype *mach, t_filetype *file);
void	print_load_command(void *lco, t_filetype *mach);
void	init_struct(t_filetype *file);
void	handle_ar(t_filetype *ar, uint8_t flags);
void	t_option(void *start, t_filetype *mach,
	void *segment_command, uint32_t ncmds);
#endif
