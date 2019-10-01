/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:00:16 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/01 22:00:19 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"
# include "op_struct.h"
# define EXEC_START (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
# define TRUE 1
# define FALSE 0

typedef enum			e_type
{
	REGISTER = 1,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	SEPARATOR,
	NEW_LINE,
	END
}						t_type;
unsigned int			g_bytes;
char					*g_buf;
typedef struct			s_token
{
	char				*content;
	t_type				type;
	unsigned			bytes;
	unsigned			data;
	struct s_token		*next;
}						t_token;
typedef struct			s_label
{
	t_token				*point;
	struct s_label		*next;
	struct s_label		*prev;
}						t_label;
typedef	struct			s_parser
{
	int					x;
	int					y;
	char				*file_name;
	int					fd;
	int					oper;
	int					arg;
	char				*name;
	char				*comment;
	char				**file;
	t_label				*labels;
	t_token				*tokens;
	t_token				*head;
}						t_parser;
void					error_lexical(int y, int x);
void					print_error_file();
void					error_syntax(int y, int x);
void					error_longname(void);
void					error_null(int y, int x);
void					error_name_comment(void);
void					error_mc(void);
void					error_endline(void);
void					error_no_label(char *str);
void					parse_name_and_comment(t_parser *par);
void					check_file_name(char *str, t_parser *par);
void					parse_name_and_comment(t_parser *par);
void					error_longcomment(void);
void					read_file(t_parser *par);
void					parse_token(t_parser *par);
void					add_token(t_parser *par, t_type type, char *content);
void					search_label(t_parser *par, char *label);
void					valid_arg(t_parser *par, t_token *token);
void					is_registry(char *string, t_parser *par);
void					is_indir_dir_label(char *string, t_parser *par,
						t_type type);
void					is_dir_or_indir(char *string, t_parser *par,
						t_type type);
void					check_args(char *string, t_parser *par);
void					filler_char_array(t_parser *par, unsigned dest);
void					bytes_in_labels(t_parser *par);
void					file_cor(t_parser *par);
void					int_to_hex(int32_t dec, int dir_size, unsigned place);
void					add_label_token(t_parser *par, char *content);
void					add_label_token2(t_parser *par, char *content);
void					new_token(t_parser *par);
void					add_label(t_parser *par, t_token *token);
void					add_token(t_parser *par, t_type type, char *content);
void					parse_args(t_parser *par, int i);
void					parse_args2(t_parser *par, int i);
void					print_usage(void);
void					error_open(void);
#endif
