#ifndef ASM_H
#define ASM_H

#include "libft/libft.h"
#include "op.h"
#include "op_struct.h"

typedef enum e_type
{
	REG = 1,
	INDIR,
	DIR,
	LABEL_DIR,
	LABEL_INDIR
}						t_type;

typedef struct			s_token
{
	t_type				* type;
	int 				oeration;
	struct s_token		*next;
	struct s_token		*prev;

}						t_token;

typedef struct			s_label
{
	char				*label;
	t_token				*point;
	struct s_label		*next;
	struct s_label		*prev;
}						t_label;

typedef	struct		s_parser
{
	int 			x;
	int 			y;
	char			*file_name;
	int             fd;
	char 			*name;
	char 			*comment;
	char 			**file;
	t_label			*labels;
	t_token			*tokens;

}					t_parser;


void 				error_lexical(int y, int x);
void				print_error_file();
void				error_syntax(int y, int x);
void				error_longname();
void                error_param();
void				error_endline();
void				parse_name_and_comment(t_parser *par);
void				check_file_name(char *str, t_parser *par);
void				parse_name_and_comment(t_parser *par);
void				error_longcomment();
void				read_file(t_parser *par);
void 				parse_token(t_parser *par);

#endif
