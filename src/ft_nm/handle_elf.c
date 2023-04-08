/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_elf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:20:53 by gemaroul          #+#    #+#             */
/*   Updated: 2022/03/10 14:22:57 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

#if __linux__

#define __bswap_16(x)					\
  ((((x) & 0xff000000u) >> 8) | (((x) & 0x00ff0000u) << 8)	\
   | (((x) & 0x0000ff00u) >> 8) | (((x) & 0x000000ffu) << 8))


static uint32_t	swap_16(uint8_t big_endian, uint32_t x)
{
	if (big_endian)
		return (__bswap_16(x));
	return (x);
}

static int ft_strstartswith(const char *str, const char *prefix)
{
    if (!str)
        return (0);

    return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}


static char coff_section_type(const char *name)
{
    if (!name)
        return ('?');

    struct s_entry
    {
        const char *section;
        char type;
    };

    static const struct s_entry entries[] = {
    { ".drectve", 'i' }, /* MSVC's .drective section */
    { ".edata", 'e' }, /* MSVC's .edata (export) section */
    { ".idata", 'i' }, /* MSVC's .idata (import) section */
    { ".pdata", 'p' }, /* MSVC's .pdata (stack unwind) section */
    { 0, 0 } };

    const struct s_entry *entry;
    for (entry = &entries[0]; entry->section; ++entry)
    {
        size_t len = ft_strlen(entry->section);
        if (ft_strncmp(name, entry->section, len) == 0 && ft_memchr(".$0123456789", name[len], 13) != 0)
            return (entry->type);
    }

    return ('?');
}

static int is_debugging(const char *name)
{
    static const char *prefixes[] = {
    ".debug",
    ".gnu.debuglto_.debug_",
    ".gnu.linkonce.wi.",
    ".zdebug",
    ".line",
    ".stab"
    };

    for (unsigned index = 0; index < sizeof(prefixes) / sizeof(prefixes[0]); ++index)
        if (ft_strstartswith(name, prefixes[index]))
            return (1);

    return (ft_strcmp(name, ".gdb_index") == 0);
}
	
static char decode_section_type(t_sects *sect)
{
    uint32_t type = sect->type;
    uint64_t flags = sect->flags;

    const char *name = sect->sect_name;

    int has_content = type != SHT_NOBITS;
    int alloc = (flags & SHF_ALLOC) != 0;
    int load = alloc && type != SHT_NOBITS;
    int read_only = (flags & SHF_WRITE) == 0;
    int code = (flags & SHF_EXECINSTR) != 0;
    int data = !code && load;
    int small_data = (flags & SHF_MIPS_GPREL) != 0 || ft_strstartswith(name, ".sbss") || ft_strstartswith(name, ".sdata");

    if (code)
        return ('t');

    if (data)
    {
        if (read_only)
            return ('r');

        //if (small_data) //seems like 2022 nm doesnt use that
        //	return ('g');

        return ('d');
    }

    if (!has_content)
    {
        if (small_data)
            return ('s');

        return ('b');
    }

    int debugging = is_debugging(name);
    if (debugging)
        return ('N');

    if (has_content && read_only)
        return ('n');

    return ('?');
}
	
char elf_symbol_decode(t_symtab_syms *sym, t_sects *sects, int64_t	nsects)
{
    if (!sym)
        return ('?');

    unsigned char bind = ELF64_ST_BIND(sym->n_type);
    unsigned char type = ELF64_ST_TYPE(sym->n_type);

    if (sym->n_sect == SHN_MIPS_SCOMMON)
        return ('c');

    if (sym->n_sect == SHN_COMMON)
        return ('C');

    if (sym->n_sect == SHN_UNDEF)
    {
        if (bind == STB_WEAK)
        {
            if (type == STT_OBJECT)
                return ('v');

            return ('w');
        }

        return ('U');
    }

    if (type == STT_GNU_IFUNC)
        return ('i');

    if (bind == STB_WEAK)
    {
        if (type == STT_OBJECT)
            return ('V');
        else
            return ('W');
    }

    if (bind == STB_GNU_UNIQUE)
        return ('u');

    if (bind != STB_LOCAL && bind != STB_GLOBAL)
        return ('?');

    char letter;
    if (sym->n_sect == SHN_ABS)
        letter = 'a';
    else if (sym->n_sect <= nsects - 1)
    {
        letter = coff_section_type(sects[sym->n_sect].sect_name);
        if (letter == '?')
            letter = decode_section_type(&sects[sym->n_sect]);
    }
    else
        return ('?');

    if (bind == STB_GLOBAL)
        letter = ft_toupper(letter);

    return (letter);
}

static int      parse_type_elf(t_list **syms, t_sects *sects,int64_t	nsects)
{
	t_list	*list;

	list = *syms;
	while (list->next)
	{
		if (list->content)
			((t_symtab_syms*)list->content)->type = elf_symbol_decode((t_symtab_syms*)list->content, sects, nsects);
		else
			return (-1);
		list = list->next;
	}
	return (1);
}

static int set_elf_struct(t_filetype *elf)
{
    char byte;

    byte = *(int8_t *)(elf->start + 4);
    if (byte == ELFCLASS32)
        elf->is_64 = 0;
    else if (byte == ELFCLASS64)
        elf->is_64 = 1;
    else
        return (-2);

    byte = *(int8_t *)(elf->start + 5);
    if (byte == ELFDATA2LSB) {
        elf->big_endian = 0;
    } 
    else if (byte == ELFDATA2MSB){
        elf->big_endian = 1;
    }
    else
        return (-2);

    byte = *(int8_t *)(elf->start + EI_VERSION);
    if (byte != EV_CURRENT)
        return (-2);

    return (1);
}

static int get_nsects32(t_filetype *elf) {
    Elf32_Ehdr hdr;
    Elf32_Shdr *section_hdr;
    Elf32_Half nsects;

    hdr = *(Elf32_Ehdr*)elf->start;
    if (check_oflow(elf, elf->start + swap32(elf->big_endian, hdr.e_shoff)))
        return (-2);
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    return (nsects);
}

static int get_nsects64(t_filetype *elf) {
    Elf64_Ehdr hdr;
    Elf64_Shdr *section_hdr;
    Elf64_Half nsects;

    hdr = *(Elf64_Ehdr*)elf->start;
    if (check_oflow(elf, elf->start + swap64(elf->big_endian, hdr.e_shoff)))
        return (-2);
    section_hdr = (Elf64_Shdr *)((char*)elf->start + swap64(elf->big_endian, hdr.e_shoff));
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    return (nsects);
}

static Elf32_Off get_section_offset_32(t_filetype *elf, const char* section_name){
    Elf32_Ehdr hdr;
    Elf32_Shdr *section_hdr;
    Elf32_Half nsects;
    Elf32_Xword size ;
    Elf32_Sym *symtab ;

    hdr = *(Elf32_Ehdr*)elf->start;
    section_hdr = (Elf32_Shdr *)((char*)elf->start + swap32(elf->big_endian, hdr.e_shoff));
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    void *shstrtab = elf->start + swap32(elf->big_endian,section_hdr[swap_16(elf->big_endian,hdr.e_shstrndx)].sh_offset);
    int i = 0;
    while (i < nsects){
        if (ft_strcmp((char*)shstrtab  + swap32(elf->big_endian,section_hdr[i].sh_name), section_name) == 0)
            return (swap32(elf->big_endian, section_hdr[i].sh_offset));
        i++;
    }
    return (-1);
}

static Elf64_Off get_section_offset_64(t_filetype *elf, const char* section_name){
    Elf64_Ehdr hdr;
    Elf64_Shdr *section_hdr;
    Elf64_Half nsects;
    Elf64_Xword size ;
    Elf64_Sym *symtab ;

    hdr = *(Elf64_Ehdr*)elf->start;
    section_hdr = (Elf64_Shdr *)((char*)elf->start + swap64(elf->big_endian, hdr.e_shoff));
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    void *shstrtab = elf->start + swap64(elf->big_endian,section_hdr[swap_16(elf->big_endian,hdr.e_shstrndx)].sh_offset);
    int i = 0;
    while (i < nsects){
        if (ft_strcmp((char*)shstrtab  + swap32(elf->big_endian,section_hdr[i].sh_name), section_name) == 0)
            return (swap64(elf->big_endian, section_hdr[i].sh_offset));
        i++;
    }
    return (-1);
}

static int get_sections64(t_filetype *elf, t_sects *sects) {
    Elf64_Ehdr hdr;
    Elf64_Shdr *section_hdr;
    Elf64_Half nsects;
    Elf64_Xword size ;
    Elf64_Sym *symtab ;

    hdr = *(Elf64_Ehdr*)elf->start;
    section_hdr = (Elf64_Shdr *)((char*)elf->start + swap64(elf->big_endian,hdr.e_shoff));
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    void *shstrtab = elf->start + swap64(elf->big_endian,section_hdr[swap_16(elf->big_endian,hdr.e_shstrndx)].sh_offset);
    if (check_oflow(elf, shstrtab))
        return (-2);
    int i = 0;
    while (i < nsects){
        if (check_oflow(elf, elf->start +swap64(elf->big_endian,section_hdr[i].sh_offset)))
            return (-2);
        sects[i].sect_name = (char*)shstrtab  + swap32(elf->big_endian,section_hdr[i].sh_name);
        sects[i].flags = swap64(elf->big_endian,section_hdr[i].sh_flags);
        sects[i].type = swap32(elf->big_endian,section_hdr[i].sh_type);
        i++;
    }
    return (1);
}

static int get_sections32(t_filetype *elf, t_sects *sects) {
    Elf32_Ehdr hdr;
    Elf32_Shdr *section_hdr;
    Elf32_Half nsects;
    Elf32_Xword size ;
    Elf32_Sym *symtab ;

    hdr = *(Elf32_Ehdr*)elf->start;

    section_hdr = (Elf32_Shdr *)((char*)elf->start + swap32(elf->big_endian, hdr.e_shoff));
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    void *shstrtab = elf->start + swap32(elf->big_endian,section_hdr[swap_16(elf->big_endian,hdr.e_shstrndx)].sh_offset);
    if (check_oflow(elf, shstrtab))
        return (-2);
    int i = 0;
    while (i < nsects){
        if (check_oflow(elf, elf->start + swap32(elf->big_endian,section_hdr[i].sh_offset)))
            return (-2);
        sects[i].sect_name = (char*)shstrtab  + swap32(elf->big_endian,section_hdr[i].sh_name);
        sects[i].flags = swap32(elf->big_endian,section_hdr[i].sh_flags);
        sects[i].type = swap32(elf->big_endian,section_hdr[i].sh_type);
        i++;
    }
    return (1);
}

static int get_symbols32(t_filetype *elf, t_list **my_syms) {
    Elf32_Ehdr hdr;
    Elf32_Shdr *section_hdr;
    Elf32_Half nsects;
    Elf32_Xword size ;
    Elf32_Sym *symtab ;
    t_symtab_syms	tmp;
    Elf32_Off strtab_offset;
    int ret;
    int j = 0;

    hdr = *(Elf32_Ehdr*)elf->start;
    ret = 0;
    section_hdr = (Elf32_Shdr *)((char*)elf->start + swap32(elf->big_endian, hdr.e_shoff));
    nsects =  swap_16(elf->big_endian, hdr.e_shnum);
    strtab_offset = get_section_offset_32(elf, ".strtab");
    if (strtab_offset == -1)
        return (ret);
    void *strtab = elf->start + strtab_offset;
    if (check_oflow(elf,strtab) == 1)
            return (-1);
    int i = 0;
    while (i < nsects){
        if (swap32(elf->big_endian,section_hdr[i].sh_type) == SHT_SYMTAB){
            long int count =  swap32(elf->big_endian,section_hdr[i].sh_size) / swap32(elf->big_endian,section_hdr[i].sh_entsize);
            Elf32_Sym *symtable = (Elf32_Sym *)((char *)elf->start + swap32(elf->big_endian, section_hdr[i].sh_offset));
            while (j < count){
                if (check_oflow(elf, (void *)&(symtable[j])) == 1)
                    return (-2);
                if ((ELF32_ST_TYPE(symtable[j].st_info) >= 3 && ELF64_ST_TYPE(symtable[j].st_info) < 5) || (symtable[j].st_info) == 0 && swap_16(elf->big_endian,symtable[j].st_shndx) == 0)
                {
                    j++;
                    continue;
                }
                tmp.n_type = symtable[j].st_info;
                tmp.n_sect = swap_16(elf->big_endian,symtable[j].st_shndx);
                tmp.n_value = swap32(elf->big_endian,symtable[j].st_value);
                if ((char*)strtab  + swap32(elf->big_endian,symtable[j].st_name))
                    tmp.name = (char*)strtab + swap32(elf->big_endian,symtable[j].st_name);
                else
                    tmp.name = NULL;
                ft_lstadd(my_syms, ft_lstnew((void *)&tmp, sizeof(tmp)));
                ret++;
                j++;
            }
        }
        i++;
    }
    return (ret);
}

static long int get_symbols64(t_filetype *elf, t_list **my_syms) {
    Elf64_Ehdr hdr;
    Elf64_Shdr *section_hdr;
    Elf64_Half nsects;
    Elf64_Xword size ;
    Elf64_Sym *symtab ;
    t_symtab_syms	tmp;
    Elf64_Off strtab_offset;
    long int ret;
    int j = 0;

    hdr = *(Elf64_Ehdr*)elf->start;
    ret = 0;
    section_hdr = (Elf64_Shdr *)((char*)elf->start + swap64(elf->big_endian, hdr.e_shoff));
    nsects = swap_16(elf->big_endian, hdr.e_shnum);
    strtab_offset = get_section_offset_64(elf, ".strtab");
    if (strtab_offset == -1)
        return (ret);
    void *strtab = elf->start + strtab_offset;
    if (check_oflow(elf,strtab) == 1)
            return (-1);
    int i = 0;
    while (i < nsects){
        if (swap32(elf->big_endian,section_hdr[i].sh_type) == SHT_SYMTAB){
            long int count =  swap64(elf->big_endian,section_hdr[i].sh_size) / swap64(elf->big_endian,section_hdr[i].sh_entsize);
            Elf64_Sym *symtable = (Elf64_Sym *)((char *)elf->start + swap64(elf->big_endian, section_hdr[i].sh_offset));
            while (j < count){
                if (check_oflow(elf, (void *)&(symtable[j])) == 1)
                    return (-2);
                if ((ELF64_ST_TYPE(symtable[j].st_info) >= 3 && ELF64_ST_TYPE(symtable[j].st_info) < 5) || (symtable[j].st_info == 0 && swap_16(elf->big_endian,symtable[j].st_shndx) == 0))
                {
                    j++;
                    continue;
                }
                tmp.n_type = symtable[j].st_info;
                tmp.n_sect = swap_16(elf->big_endian,symtable[j].st_shndx);
                tmp.n_value = swap64(elf->big_endian,symtable[j].st_value);
                if ((char*)strtab  + swap32(elf->big_endian,symtable[j].st_name))
                    tmp.name = (char*)strtab + swap32(elf->big_endian,symtable[j].st_name);
                else
                    tmp.name = NULL;
                ft_lstadd(my_syms, ft_lstnew((void *)&tmp, sizeof(tmp)));
                ret++;
                j++;
            }
        }
        i++;
    }
    return (ret);
}

static void	del(void *content, size_t size)
{
	t_symtab_syms	*tmp;

	if (content && size != 0)
	{
		tmp = (t_symtab_syms *)content;
		free(content);
	}
}


static int		print_syms_elf(t_filetype *mach, t_list **syms)
{
	int				pad_size;
	t_list			*sym;
	t_symtab_syms	*tmp;
    int count;

    count = 0;
	sym = *syms;
	while (sym->content && sym->next)
	{
		tmp = (t_symtab_syms *)sym->content;
        if (tmp->n_sect == 0 && ELF64_ST_BIND(tmp->n_type) == 0&& ELF64_ST_TYPE(tmp->n_type) == 0){
            sym = sym->next;
            continue;
        }
		if (tmp->type != '-')
		{
			pad_size = (mach->is_64) ? 16 : 8;
			if (tmp->name)
			{
				if (tmp->type == 'U' || (tmp->n_value == 0 &&\
                (tmp->n_sect == 0 && \
                (tmp->type == 'w' || tmp->type == 'W' || tmp->type == 'u' || tmp->type == 'v' || tmp->type == 'V'))))
                {
					inner_print_sym(1, pad_size, tmp);
                }
				else if (mach->is_64)
					inner_print_sym(2, pad_size, tmp);
				else
					inner_print_sym(3, pad_size, tmp);
                count++;
			}
		}
		sym = sym->next;
	}
    return (count);
}


int handle_elf(uint32_t magic_number,int argc, t_filetype *file)
{
    t_list	*syms;
	t_sects	*sects;
	int64_t	nsects;
    int chk = 0;

    if (set_elf_struct(file) != 1){
        return (error_ret(-2, file->name, NULL, NULL));
    }
    if (check_oflow(file, file->start))
        return (error_ret(-2, file->name, NULL, NULL));
    (argc > 2) ? ft_printf("\n%s:\n", file->name) : 0;
    if (file->is_64){
        if ((nsects = get_nsects64(file)) < 0) 
            return(error_ret(-2, file->name, NULL, NULL));
        if (!(sects = (t_sects *)malloc(sizeof(t_sects) * nsects)))
		    return (-1);
        if (get_sections64(file, sects) < 0)
            return(error_ret(-2, file->name, NULL, NULL));
        if (!(syms = ft_lstnew(NULL, 0)))
        {
            sects ? free(sects) : 0;
            return (-1);
        }
        if ((chk = get_symbols64(file, &syms)) <= 0){
            if (chk != -2)
                ft_printf("ft_nm: %s: no symbols\n", file->name);
            ft_lstdel(&syms, del);
		    (syms) ? free(syms) : 0;
            (sects) ? free(sects) : 0;
		    return (chk);
        }
    }  
    else
    {
        if ((nsects = get_nsects32(file)) < 0){ 
            return(error_ret(-2, file->name, NULL, NULL));
        }
        if (!(sects = (t_sects *)malloc(sizeof(t_sects) * nsects)))
		    return (-1);
        if (get_sections32(file, sects) < 0)
            return(error_ret(-2, file->name, NULL, NULL));
        if (!(syms = ft_lstnew(NULL, 0)))
        {
            sects ? free(sects) : 0;
            return (-1);
        }
        if ((chk = get_symbols32(file, &syms)) <= 0){
            if (chk != -2)
                ft_printf("ft_nm: %s: no symbols\n", file->name);
            ft_lstdel(&syms, del);
		    (syms) ? free(syms) : 0;
            (sects) ? free(sects) : 0;
		    return (chk);
        }
    }
    if ((chk = parse_type_elf(&syms, sects, nsects)) == -1)
	{
        ft_lstdel(&syms, del);
        (syms) ? free(syms) : 0;
        (sects) ? free(sects) : 0;
        return (-1);
	}
    ft_lstsort_nm(syms, sort_mysyms_alpha_elf);
    print_syms_elf(file, &syms);
    ft_lstdel(&syms, del);
	(syms) ? free(syms) : 0;
    (sects) ? free(sects) : 0;
    return (1);
}
#endif
