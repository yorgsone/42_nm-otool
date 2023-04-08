# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 03:07:26 by gemaroul          #+#    #+#              #
#    Updated: 2018/10/30 00:49:52 by gemaroul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# COMPILATION
CC = gcc
CCFLAGS = -Wall -Werror -Wextra

LNK = gcc
LNKFLAGS =

# DIRECTORIES
SRCDIR = src
OBJDIR = obj
INCDIR = include


# SOURCES
SRC =\
	str/ft_putendl.c\
	str/ft_strchri_lu.c\
	str/ft_striter.c\
	str/ft_strncat.c\
	str/ft_strrchr.c\
	str/ft_putendl_fd.c\
	str/ft_strclr.c\
	str/ft_striteri.c\
	str/ft_strncmp.c\
	str/ft_strsplit.c\
	str/ft_putstr.c\
	str/ft_strcmp.c\
	str/ft_strjoin.c\
	str/ft_strnjoin.c\
	str/ft_strncpy.c\
	str/ft_strstr.c\
	str/ft_putstr_fd.c\
	str/ft_strcpy.c\
	str/ft_strlcat.c\
	str/ft_strndup.c\
	str/ft_strsub.c\
	str/ft_strcat.c\
	str/ft_strdel.c\
	str/ft_strlen.c\
	str/ft_strnequ.c\
	str/ft_strtrim.c\
	str/ft_strchr.c\
	str/ft_strchr_b.c\
	str/ft_strdup.c\
	str/ft_strmap.c\
	str/ft_strnew.c\
	str/ft_wordlen.c\
	str/ft_strchri.c\
	str/ft_strequ.c\
	str/ft_strmapi.c\
	str/ft_strnstr.c\
	str/ft_wstrlen.c\
	str/ft_wordlen.c\
	str/ft_wordcount.c\
	str/ft_strjoinfree.c\
	str/ft_strnjoinfree.c\
	str/ft_strmove.c\
	str/ft_strreplace.c\
	str/ft_strtolower.c\
	str/ft_strunicode.c\
	mem/ft_bzero.c\
	mem/ft_memccpy.c\
	mem/ft_memcmp.c\
	mem/ft_memdel.c\
	mem/ft_memset.c\
	mem/ft_memalloc.c\
	mem/ft_memchr.c\
	mem/ft_memcpy.c\
	mem/ft_memmove.c\
	char/ft_putchar.c\
	char/ft_putchar_fd.c\
	char/ft_wcharlen.c\
	converse/ft_atoi.c\
	converse/ft_itoa.c\
	converse/ft_tolower.c\
	converse/ft_toupper.c\
	converse/ft_ftoa.c\
	converse/ft_itoa_base.c\
	converse/ft_utoa_base.c\
	converse/ft_convertunicode.c\
	converse/ft_atol.c\
	checks/ft_isalnum.c\
	checks/ft_isascii.c\
	checks/ft_islower.c\
	checks/ft_isupper.c\
	checks/ft_isalpha.c\
	checks/ft_isdigit.c\
	checks/ft_isprint.c\
	checks/ft_pow.c\
	checks/ft_checkunicode.c\
	number/ft_putnbr.c\
	number/ft_putnbr_fd.c\
	number/ft_intcpy.c\
	number/ft_intdup.c\
	number/ft_intndup.c\
	number/sort_int_tab.c\
	containers/lst/ft_lstadd.c\
	containers/lst/ft_lstdelone.c\
	containers/lst/ft_lstmap.c\
	containers/lst/ft_lstdel.c\
	containers/lst/ft_lstiter.c\
	containers/lst/ft_lstnew.c\
	containers/lst/ft_lstsort.c\
	containers/stack/ft_newstack.c\
	containers/stack/ft_isfull.c\
	containers/stack/ft_isempty.c\
	containers/stack/ft_push.c\
	containers/stack/ft_peek.c\
	containers/stack/ft_pop.c\
	gnl/get_next_line.c\
	ft_printf/ft_printf.c\
	ft_printf/assign.c\
	ft_printf/alpha.c\
	ft_printf/handle.c\
	ft_printf/process.c\
	ft_printf/ft_form.c\
	ft_printf/snb1.c\
	ft_printf/snb2.c\
	ft_printf/unb1.c\
	ft_printf/unb2.c\
	ft_printf/printfbuf.c\
	ft_printf/sprintf.c\
	ft_getopt/ft_getopt.c

.PHONY: all clean fclean re 

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJS_DIRS = $(sort $(dir $(OBJS)))

INCS_DIRS = $(addsuffix /, $(INCDIR))
INCS = $(addprefix -I , $(INCS_DIRS))

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "** libft **"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJS_DIRS)
	@$(CC) -c -o $@ $< $(INCS) $(CCFLAGS)

clean:
	@rm -f $(LIBS)
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean:	clean
	@rm -f $(NAME)

re: fclean all