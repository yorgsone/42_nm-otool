/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_command_name.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:22:56 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:23:02 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADING_COMMAND_NAME_H
# define LOADING_COMMAND_NAME_H

# include "ft_otool.h"
# include "time.h"

typedef struct	s_lc
{
	uint32_t	cmd;
	char		*cmd_name;
	void		(*print_seg)(void *seg, const struct s_lc *info,
				uint8_t is_big_endian);
}				t_lc;

void			print_sc64(void *seg, const t_lc *info,
				uint8_t is_big_endian);
void			print_sc(void *seg, const t_lc *info,
				uint8_t is_big_endian);
void			print_symtab_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_symseg_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_thread_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_fvmlib_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_ident_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_fvmfile_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_dysymtab_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_dylib_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_dylinker_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_prebound_dylib_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_routines_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_sub_framework_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_sub_umbrella_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_sub_client_command(void *com, const t_lc *info,
					uint8_t is_big_endian);
void			print_sub_library_command(void *com, const t_lc *info,
					uint8_t is_big_endian);
void			print_twolevel_hints_command(void *com, const t_lc *info,
					uint8_t is_big_endian);
void			print_prebind_cksum_command(void *com, const t_lc *info,
					uint8_t is_big_endian);
void			print_routines_command_64(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_uuid_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_rpath_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_linkedit_data_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_encryption_info_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_dyld_info_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_version_min_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_entry_point_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_source_version_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_encryption_info_command_64(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_note_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_linker_option_command(void *com, const t_lc *info,
				uint8_t is_big_endian);
void			print_build_version_command(void *com, const t_lc *info,
				uint8_t is_big_endian);

#if __MACH__
static const t_lc g_loading_commands_table[] =
{
	{LC_SEGMENT, "LC_SEGMENT", &print_sc},
	{LC_SYMTAB, "LC_SYMTAB", &print_symtab_command},
	{LC_SYMSEG, "LC_SYMSEG", &print_symseg_command},
	{LC_THREAD, "LC_THREAD", &print_thread_command},
	{LC_UNIXTHREAD, "LC_UNIXTHREAD", &print_thread_command},
	{LC_LOADFVMLIB, "LC_LOADFVMLIB", &print_fvmlib_command},
	{LC_IDFVMLIB, "LC_IDFVMLIB", &print_fvmlib_command},
	{LC_IDENT, "LC_IDENT", &print_ident_command},
	{LC_FVMFILE, "LC_FVMFILE", &print_fvmfile_command},
	{LC_PREPAGE, "LC_PREPAGE", NULL},
	{LC_DYSYMTAB, "LC_DYSYMTAB", &print_dysymtab_command},
	{LC_LOAD_DYLIB, "LC_LOAD_DYLIB", &print_dylib_command},
	{LC_ID_DYLIB, "LC_ID_DYLIB", &print_dylib_command},
	{LC_LOAD_DYLINKER, "LC_LOAD_DYLINKER", &print_dylinker_command},
	{LC_ID_DYLINKER, "LC_ID_DYLINKER", &print_dylinker_command},
	{LC_PREBOUND_DYLIB, "LC_PREBOUND_DYLIB", &print_prebound_dylib_command},
	{LC_ROUTINES, "LC_ROUTINES", &print_routines_command},
	{LC_SUB_FRAMEWORK, "LC_SUB_FRAMEWORK", &print_sub_framework_command},
	{LC_SUB_UMBRELLA, "LC_SUB_UMBRELLA", &print_sub_umbrella_command},
	{LC_SUB_CLIENT, "LC_SUB_CLIENT", &print_sub_client_command},
	{LC_SUB_LIBRARY, "LC_SUB_LIBRARY", &print_sub_library_command},
	{LC_TWOLEVEL_HINTS, "LC_TWOLEVEL_HINTS", &print_twolevel_hints_command},
	{LC_PREBIND_CKSUM, "LC_PREBIND_CKSUM", &print_prebind_cksum_command},
	{LC_LOAD_WEAK_DYLIB, "LC_LOAD_WEAK_DYLIB", &print_dylib_command},
	{LC_SEGMENT_64, "LC_SEGMENT_64", &print_sc64},
	{LC_ROUTINES_64, "LC_ROUTINES_64", &print_routines_command_64},
	{LC_UUID, "LC_UUID", &print_uuid_command},
	{LC_RPATH, "LC_RPATH", &print_rpath_command},
	{LC_CODE_SIGNATURE, "LC_CODE_SIGNATURE",\
		&print_linkedit_data_command},
	{LC_SEGMENT_SPLIT_INFO, "LC_SEGMENT_SPLIT_INFO",\
		&print_linkedit_data_command},
	{LC_REEXPORT_DYLIB, "LC_REEXPORT_DYLIB", &print_dylib_command},
	{LC_LAZY_LOAD_DYLIB, "LC_LAZY_LOAD_DYLIB", NULL},
	{LC_ENCRYPTION_INFO, "LC_ENCRYPTION_INFO", &print_encryption_info_command},
	{LC_DYLD_INFO, "LC_DYLD_INFO", &print_dyld_info_command},
	{LC_DYLD_INFO_ONLY, "LC_DYLD_INFO_ONLY", &print_dyld_info_command},
	{LC_LOAD_UPWARD_DYLIB, "LC_LOAD_UPWARD_DYLIB", NULL},
	{LC_VERSION_MIN_MACOSX, "LC_VERSION_MIN_MACOSX",\
		&print_version_min_command},
	{LC_VERSION_MIN_IPHONEOS, "LC_VERSION_MIN_IPHONEOS",\
		&print_version_min_command},
	{LC_FUNCTION_STARTS, "LC_FUNCTION_STARTS", &print_linkedit_data_command},
	{LC_DYLD_ENVIRONMENT, "LC_DYLD_ENVIRONMENT", &print_dylinker_command},
	{LC_MAIN, "LC_MAIN", &print_entry_point_command},
	{LC_DATA_IN_CODE, "LC_DATA_IN_CODE", &print_linkedit_data_command},
	{LC_SOURCE_VERSION, "LC_SOURCE_VERSION", &print_source_version_command},
	{LC_DYLIB_CODE_SIGN_DRS, "LC_DYLIB_CODE_SIGN_DRS",\
		&print_linkedit_data_command},
	{LC_ENCRYPTION_INFO_64, "LC_ENCRYPTION_INFO_64",\
		&print_encryption_info_command_64},
	{LC_LINKER_OPTION, "LC_LINKER_OPTION", &print_linker_option_command},
	{LC_LINKER_OPTIMIZATION_HINT, "LC_LINKER_OPTIMIZATION_HINT",\
		&print_linkedit_data_command},
	{LC_VERSION_MIN_TVOS, "LC_VERSION_MIN_TVOS", &print_version_min_command},
	{LC_VERSION_MIN_WATCHOS, "LC_VERSION_MIN_WATCHOS",\
		&print_version_min_command},
	{LC_NOTE, "LC_NOTE", &print_note_command},
	{LC_BUILD_VERSION, "LC_BUILD_VERSION", &print_build_version_command},
	{LC_DYLD_EXPORTS_TRIE, "LC_DYLD_EXPORTS_TRIE", &print_version_min_command},
	{LC_DYLD_CHAINED_FIXUPS, "LC_DYLD_CHAINED_FIXUPS",\
		&print_version_min_command},
	{0, NULL, NULL}
};
#endif

const t_lc		*g_loading_commands_table_infos();
const t_lc		*lc_info_from_id(uint32_t id);

#endif
