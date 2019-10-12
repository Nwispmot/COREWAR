# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/05 19:40:38 by nwispmot          #+#    #+#              #
#    Updated: 2018/12/05 20:05:14 by nwispmot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_H   = ./includes
OBJ_DIR = ./obj

NAME    = libft.a
SRC     = char_str.c \
            check.c \
            float.c \
            ft_atoi.c \
            ft_atoi_base.c \
            ft_atol.c \
            ft_bzero.c \
            ft_count_if.c \
            ft_is_negative.c \
            ft_isalnum.c \
            ft_isalpha.c \
            ft_isascii.c \
            ft_isdigit.c \
            ft_isprint.c \
            ft_itoa.c \
            ft_lstadd.c \
            ft_lstdel.c \
            ft_lstdelone.c \
            ft_lstiter.c \
            ft_lstmap.c \
            ft_lstnew.c \
            ft_ltoa.c \
            ft_ltoa_base.c \
            ft_memalloc.c \
            ft_memccpy.c \
            ft_memchr.c \
            ft_memcmp.c \
            ft_memcpy.c \
            ft_memdel.c \
            ft_memmove.c \
            ft_memset.c \
            ft_pow.c \
            ft_printf.c \
            ft_putchar.c \
            ft_putchar_fd.c \
            ft_putendl.c \
            ft_putendl_fd.c \
            ft_putnbr.c \
            ft_putnbr_fd.c \
            ft_putstr.c \
            ft_putstr_fd.c \
            ft_range.c \
            ft_recursive_factorial.c \
            ft_sqrt.c \
            ft_strcat.c \
            ft_strchr.c \
            ft_strclr.c \
            ft_strcmp.c \
            ft_strcpy.c \
            ft_strdel.c \
            ft_strdup.c \
            ft_strdup_free.c \
            ft_strequ.c \
            ft_striter.c \
            ft_striteri.c \
            ft_strjoin.c \
            ft_strjoin_free.c \
            ft_strlcat.c \
            ft_strlen.c \
            ft_strmap.c \
            ft_strmapi.c \
            ft_strncat.c \
            ft_strncmp.c \
            ft_strncpy.c \
            ft_strnequ.c \
            ft_strnew.c \
            ft_strnstr.c \
            ft_strrchr.c \
            ft_strsplit.c \
            ft_strsplit_n.c \
            ft_strsplit_tab_space.c \
            ft_strstr.c \
            ft_strsub.c \
            ft_strsub_free.c \
            ft_strtrim.c \
            ft_swap.c \
            ft_swap_d.c \
            ft_tolower.c \
            ft_toupper.c \
            ft_utoa.c \
            ftoa.c \
            get_next_line.c \
            int_dec.c \
            lhex.c \
            octal.c \
            parse.c \
            percent_sharp.c \
            pointer.c \
            uhex.c \
            unsigned.c \
            width.c \
            ft_isspace.c

OBJ     = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

CC      = gcc
FLAGS   = -Wall -Wextra -Werror
INC     = -I $(LIB_H)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo ✅ Library Libft created.

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(addprefix $(OBJ_DIR)/, %.o): %.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)
	@echo Libft Object Files deleted.

fclean: clean
	rm -f $(NAME)
	@echo Libft Library deleted.

re: fclean all
