#ifndef ASM_H
#define ASM_H

#include "libft/libft.h"
#include "op.h"
#include "op_struct.h"
# define EXEC_START (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

unsigned int g_bytes;
char	*g_buf;

//static char				*g_type[] = {
//		"COMMAND",
//		"STRING",
//		"LABEL",
//		"OPERATOR",
//		"REGISTER",
//		"DIRECT",
//		"DIRECT_LABEL",
//		"INDIRECT",
//		"INDIRECT_LABEL",
//		"SEPARATOR",
//		"NEW_LINE",
//		"END"
//};

typedef struct			s_token
{
	char				*content;
	t_type				type;
	struct s_token		*next;
}						t_token;

typedef	struct		s_parser
{
	int 			x;
	int 			y;
	char			*file_name;
	int             fd;
	int             oper;
	char 			*name;
	char 			*comment;
	char 			**file;
	//t_label			*labels;
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
