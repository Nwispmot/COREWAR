#ifndef ASM_H
#define ASM_H

#include "libft/libft.h"
#include "op.h"



typedef	struct		s_parser
{
	int 			x;
	int 			y;
    char			*file_name;
    int             fd;
    char 			*name;
    char 			*comment;
    char 			**file;

}					t_parser;

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

void				print_error_file();
void 				error_usage(void);
void				error_no_file(char *argv);
void 				error_lexical(int y, int x);
void 				error_syntax(int str, char *oper);
void 				error_exit(void);

#endif
