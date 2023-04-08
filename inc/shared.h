/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:20:53 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:20:57 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# if __MACH__
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/arch.h>
# include <mach/machine.h>
# include <mach-o/arch.h>
# include <mach-o/nlist.h>
# endif 
#if __linux__
# include <elf.h>
#endif
# include <ar.h>

# include <sys/stat.h>
# include <inttypes.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/mman.h>

# include <stdint.h>
# include "../libft/include/libft.h"

# define AR_1 "#1/"
# define TRUE 1
# define FALSE 0

typedef struct		s_filetype
{
	void		*start;
	void		*end;
	char		*name;
	char		*symname;
	uint8_t		flags;
	uint8_t		is_64;
	uint8_t		big_endian;
	uint32_t	magic;
	off_t		size;
}					t_filetype;

typedef struct		s_sects
{
	uint32_t type;
	uint64_t flags;
	char *sect_name;
}					t_sects;

typedef struct ar_hdr	*t_ar;
# if __MACH__
typedef struct mach_header	*t_mhdr;
typedef struct segment_command_64	t_sc64;
typedef struct segment_command	t_sc;
typedef struct section_64	t_s64;
typedef struct section	t_s;
typedef struct load_command	t_lco;
typedef struct fat_arch	t_fa;
typedef struct fat_header	t_fh;
# endif 

int					is_macho(uint32_t magic, t_filetype *file);
int					is_fat(uint32_t magic, t_filetype *file);
int					is_archive(uint32_t magic, t_filetype *file);

int					is_elf(uint32_t magic, t_filetype *file);

int					print_macho_header(t_filetype *mach, void *macho_header);
int					check_oflow(t_filetype *file, void *ptr);
int					is_text_section(t_filetype *mach, void *sect);
int					error_ret(int err_code, const char *err_file,
					const char *err_msg, t_sects *to_free);
# if __MACH__
int					check_lc_errors(struct load_command *lc, t_filetype *mach);
# endif 
void				*o_mmap(int fd, off_t *size);
void				ft_hexdump_line_values(char *start, int64_t len,
					t_filetype *file);
void				ft_hexdump(void *start, int64_t size,
	int64_t start_address, t_filetype *file);
void				init_struct(t_filetype *file);
void				error(char *at, char *error);

uint32_t			ft_bswap_uint32(uint32_t x);
uint64_t			ft_bswap_uint64(uint64_t x);
uint32_t			swap32(uint8_t big_endian, uint32_t x);
uint64_t			swap64(uint8_t big_endian, uint64_t x);
size_t				ft_pow2(size_t n, size_t pow);
struct fat_arch		*get_archs(struct fat_arch *archs,
	t_filetype *fat, size_t nfat_arch);
# if __MACH__
void				free_nxinfo(const NXArchInfo *o1, const NXArchInfo *o2);
int32_t				ft_bswap_int32(int swap, int32_t x);
const NXArchInfo	*get_local_arch(struct fat_arch *fat_archs,
uint32_t nfat_arch, const NXArchInfo *local_arch, const NXArchInfo *from_name);
# endif 
#endif
