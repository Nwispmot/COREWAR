#include "asm.h"

void print_error_file()
{
	ft_printf("Invalid file format\n");
	exit(0);
}

void error_usage(void) //if no file
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>");
	exit (0);
}

void error_no_file(char *argv) //if fd < 2!!!
{
	ft_printf("Can't read source file %s", argv);
	exit (0);
}

void error_lexical(int y, int x)
{
	ft_printf("Lexical error at [%d:%d]", y + 1, x + 1);
	exit (0);
}

//void error_syntax(int str, char *oper)
//{
//	ft_printf("Syntax error at token [TOKEN][%d] INSTRUCTION \"%s\"", str, oper);
//	exit (0);
//}

void error_exit(void) {
	ft_printf("Error!!!!!!!!!");
}
