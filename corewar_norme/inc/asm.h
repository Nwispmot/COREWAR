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
# include "../libft/libft.h"
# include "op.h"
# include "op_struct.h"
# define EXEC_START (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)

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
	int					flag;
	char				*name;
	char				*comment;
	char				**file;
	t_label				*labels;
	t_token				*tokens;
	t_token				*head;
}						t_parser;

/*
**	errors
**	errors.c	error_file.c	error_usage.c
*/
void					error_lexical(int y, int x);
void					print_error_file();
void					error_syntax(int y, int x);
void					error_longname(void);
void					error_null(int y, int x);
void					error_name_comment(void);
void					error_mc(void);
void					error_quotes(void);
void					error_endline(void);
void					error_param_count();
void					error_no_label(char *str);
void					error_longcomment(void);
void					print_usage(void);
void					error_open(void);
/*
**	asm.c
*/
void					parse_args(t_parser *par, int i);
void					parse_args2(t_parser *par, int i);
void					parse_token(t_parser *par);
void					param_count(t_parser *par, int args, int *i);
/*
**	add_label_token.c
*/
void					add_label(t_parser *par, t_token *token);
void					add_token(t_parser *par, t_type type, char *content);
void					add_label_token(t_parser *par, char *content);
void					add_label_token2(t_parser *par, char *content);
/*
**	args_types.c
*/
void					valid_arg(t_parser *par, t_token *token);
void					is_registry(char *string, t_parser *par);
void					is_indir_dir_label(char *string, t_parser *par,
						t_type type);
void					is_dir_or_indir(char *string, t_parser *par,
						t_type type);
void					check_args(char *string, t_parser *par);
/*
**	create.c
*/
void					bytes_in_labels(t_parser *par);
void					file_cor(t_parser *par);
void					search_label(t_parser *par, char *label);
unsigned				add_bytes(t_token *operator, char *label,
						t_parser *par);
/*
**	fill.c
*/
void					fill_and_create(t_parser *parser);
void					filler_char_array(t_parser *par, unsigned dest);
void					fill_args_data(t_parser *par, unsigned *dest);
void					code_of_args_type(t_token *op, unsigned dest,
						u_int8_t n_arg);
void					int_to_hex(int32_t dec, int dir_size, unsigned place);
/*
**	name_comment.c
*/
void					read_file(t_parser *par);
void					check_end_line(char *str);
void					parse_name_and_comment(t_parser *par);
void					check_name_of_comment(t_parser *par, char *string,
						int i);
void					check_file_name(char *str, t_parser *par);
/*
**	parse_tokens.c
*/
int						label_or_comand(char *str, t_parser *par, int *i);
int						is_operation(char *string, t_parser *par, int i);
char					*check_oper(char *string, int *or);
int						is_label(char *str, t_parser *par);
/*
**	new_token.c
*/
void					new_token(t_parser *par);
int						new_token2(t_parser *par, int i);
void					new_token3(t_parser *par, int *i, int *flag,
						int *label);
/*
**	new_name_or_commit.c
*/
void					new_name_or_commit(char *string, t_parser *par, int be);
void					new_name_or_commit2(char **str, t_parser *par);
/*
**	quotes.c
*/
char					*quotes(char *str, int *i1, int *j1, t_parser *par);
int						quotes2(char **str, t_parser *par);
int						while_next_space(char *str, int i, t_parser *par);
char					*quotes3(char *str, int *i1, int i, t_parser *par);
#endif
