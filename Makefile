CC			= gcc
INC			= -I includes
FLAGS		= -Wall -Wextra -Werror $(INC)
INC_PATH 	= inc
LIB_PATH	= libft
BUILD_PATH	= obj
SRC_PATH	= src
UNAME			= $(shell uname)

NM_SOURCES = ft_nm/ft_nm.c ft_nm/handle_ar.c ft_nm/sort_lst.c ft_nm/handle_macho.c ft_nm/handle_fat.c
NM_SOURCES += ft_nm/handle_macho2.c ft_nm/handle_macho3.c ft_nm/handle_macho4.c
NM_SOURCES += ft_nm/handle_elf.c

ifeq ($(UNAME),Darwin)
OTOOL_SOURCES = ft_otool/ft_otool.c ft_otool/handle_ar.c ft_otool/handle_fat.c
OTOOL_SOURCES += ft_otool/handle_mach_o.c ft_otool/handle_mach_o2.c ft_otool/loading_command_name.c ft_otool/chk_flag.c
OTOOL_SOURCES += ft_otool/print_load_commands_00.c  ft_otool/print_load_commands_01.c ft_otool/ft_getopt.c
OTOOL_SOURCES += ft_otool/print_load_commands_02.c ft_otool/print_load_commands_03.c ft_otool/print_load_commands_04.c
OTOOL_SOURCES += ft_otool/print_load_commands_05.c ft_otool/print_load_commands_06.c ft_otool/print_load_commands_07.c
OTOOL_SOURCES += ft_otool/print_load_commands_08.c ft_otool/print_load_commands_09.c
endif

SHARED_SOURCES = shared/shared.c shared/shared2.c shared/shared3.c shared/shared4.c shared/tools.c shared/ft_pow2.c
NM_SOURCES += $(SHARED_SOURCES)

ifeq ($(UNAME),Darwin)
OTOOL_SHARED_SOURCES	= $(OTOOL_SOURCES) $(SHARED_SOURCES)
endif

LIB_SOURCES = $(LIB_PATH)/libft.a

OBJECTS_NM	= $(NM_SOURCES:%.c=$(BUILD_PATH)/%.o)
ifeq ($(UNAME),Darwin)
OBJECTS_OTOOL = $(OTOOL_SHARED_SOURCES:%.c=$(BUILD_PATH)/%.o)
endif
OBJECTS_SHARED = $(SHARED_SOURCES:%.c=$(BUILD_PATH)/%.o)

NAME = nm_otool
NM = ft_nm
OTOOL = ft_otool

.PHONY: all clean fclean re $(NAME)

ifeq ($(UNAME),Linux)
all: $(NM)
endif

ifeq ($(UNAME),Darwin)
all: $(NM) $(OTOOL)

$(OTOOL): $(OBJECTS_OTOOL)
	@make -s -C $(LIB_PATH)
	@$(CC) $(FLAGS_CC) -o $@ $(OBJECTS_OTOOL) $(LIB_SOURCES)
	@echo 'ft_otool ✅'

endif

$(NM):  $(OBJECTS_NM)
	@make -s -C $(LIB_PATH)
	@$(CC) $(FLAGS_CC) -o $@ $(OBJECTS_NM) $(LIB_SOURCES)
	@echo 'ft_nm ✅'


$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS_CC) -c -o $@ $< -I $(INC_PATH)

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(BUILD_PATH)
	@echo "** clean **"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NM) $(OTOOL) $(LIB_NAME)
	@echo "** fclean **"

re: fclean
	@make all