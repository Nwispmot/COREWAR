OBJ_DIR	 	= ./obj
LIB_DIR	 	= ./libft

NAME		= asm
LIBFT 		= $(LIB_DIR)/libft.a

SRC_FOLDER	= asm.c \
			add_label_token.c \
			args_types.c \
			errors.c \
			error_file.c \
			error_usage.c \
			create.c \
			fill.c \
			name_comment.c  \
			parse_tokens.c \
			new_token.c \
			new_name_or_commit.c \
			quotes.c \

SRC_PATH	= ./src
SRC 		= $(addprefix $(SRC_PATH)/,$(SRC_FOLDER))
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC_FOLDER:.c=.o))
CC			= gcc
CFLAGS	 	= -Wall -Wextra -Werror -g
LIB_INC 	= -I $(LIB_DIR)/includes
LIB_LINK	= -L $(LIB_DIR) -lft

all: $(NAME)

$(LIBFT):
	@make -C $(LIB_DIR) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_INC) $(LIB_LINK) -o $(NAME)
	@echo ✅ Assembler Executable created.

$(addprefix $(OBJ_DIR)/, %.o): $(addprefix $(SRC_PATH)/,%.c) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LIB_INC) -c $< -o $@

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rf $(OBJ_DIR)
	@echo ❌ Assembler Object files deleted.

fclean: clean
	@make -C $(LIB_DIR) fclean --no-print-directory
	rm -f $(NAME)
	@echo ❌ Assembler Executable deleted.

re: fclean all
