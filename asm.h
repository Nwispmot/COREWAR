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

void				print_error_file();
void 				error_usage(void);
void				error_no_file(char *argv);
void 				error_lexical(int str);
void 				error_syntax(int str, char *oper);
void 				error_exit(void);
#endif //COREWAR_ASM_H
