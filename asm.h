#ifndef ASM_H
#define ASM_H

#include "libft/libft.h"
#include "op.h"

typedef struct			s_token
{

	//t_type				type;
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

}					t_parser;


void 				error_lexical(int y, int x);
void				print_error_file();
void				error_syntax(int y, int x);
void				error_longname();
void				error_endline();
void				parse_name_and_comment(t_parser *par);
void				check_file_name(char *str, t_parser *par);
void				parse_name_and_comment(t_parser *par);
void				error_longcomment();

#endif
