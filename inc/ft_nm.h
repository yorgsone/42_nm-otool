/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:22:49 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:22:50 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# if __MACH__
#  include <mach-o/fat.h>
#  include <mach-o/loader.h>
#  include <mach-o/nlist.h>
#  include <mach/machine.h>
#  include <mach-o/arch.h>
# endif 
# include <ar.h>
# include <sys/stat.h>
# include <inttypes.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/mman.h>


# include "shared.h"

typedef struct	s_symtab_syms
{
	char		type;
	uint8_t		n_type;
	uint16_t	n_sect;
	uint16_t	flags;
	int16_t		n_desc;
	uint64_t	n_value;
	char		*name;
}				t_symtab_syms;

void			*o_mmap(int fd, off_t *size);
void			init_struct(t_filetype *file);
void			handle_ar(t_filetype *ar);
void			ft_lstsort_nm(t_list *lst, int (*f)(t_list *lst1, t_list *lst2));
void			print_syms(t_filetype *mach, t_list **syms);
void			inner_print_sym(int select, int pad_size, t_symtab_syms *sym);
void			assign_type(t_symtab_syms *sym, t_sects *sects);
# if __MACH__
void			add_sym_32(struct nlist *symbols_d, t_list **my_syms,
				t_filetype *mach, t_filetype *file);
void			add_sym_64(struct nlist_64 *symbols_d64, t_list **my_syms,
				t_filetype *mach, t_filetype *file);
				int				handle_mach_o(int argc, t_filetype *mach, t_filetype *file);
				int				parse_symtab_command(t_filetype *mach, void *load_command,
				t_list **my_syms, t_filetype *file);
# endif 
int				is_macho(uint32_t magic, t_filetype *file);
int				parse_type(t_list **syms, t_sects *sects);
int				is_fat(uint32_t magic, t_filetype *file);
int				is_archive(uint32_t magic, t_filetype *file);

int				handle_fat(t_filetype *file);
#if __linux__
int 			handle_elf(uint32_t magic_number,int argc, t_filetype *file);
#endif
int				ft_nm(int argc, char *name);
int				sort_mysyms_alpha(t_list *lst1, t_list *lst2);
int				find_symtab(t_filetype *mach, void *start,
				t_list **my_syms, t_filetype *file);
int				save_syms_64(void *ptr, t_list **my_syms,
				t_filetype *mach, t_filetype *file);
int				save_syms_32(void *ptr, t_list **my_syms,
				t_filetype *mach, t_filetype *file);
uint32_t		get_count_sects(t_filetype *mach, void *lc);
uint32_t		store_sectname(t_filetype *mach, void *section,
				t_sects *sects, uint32_t index);
uint32_t		get_nsect_count(t_filetype *mach, void *segment,
				uint32_t nsect_count);
char			get_sect_type(uint8_t n_type, t_sects *sect);
char			*ft_strdup_overflow(t_filetype *file, char *src, char end_char);
int				sort_mysyms_alpha_elf(t_list *lst1, t_list *lst2);
#endif
