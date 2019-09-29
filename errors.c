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
	ft_printf("Lexical error at [%d:%d]\n", y + 1, x + 1);
	exit (0);
}

void error_syntax(int y, int x)
{
	ft_printf("Syntax error at token [%d:%d]\n", y + 1, x + 1);
	exit (0);
}

void error_exit(void) {
	ft_printf("Error!!!!!!!!!");
}

void error_endline()
{
	ft_printf("Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)\n");
	exit(0);
}

void error_longname()
{
	ft_printf("Champion name too long (Max length 128)\n");
	exit(0);
}

void error_longcomment()
{
	ft_printf("Champion comment too long (Max length 2048)\n");
	exit(0);
}

void error_name_comment()
{
    ft_printf("No name or comment\n");
    exit(0);
}

void error_no_label(char *str)
{
    ft_printf("No such label at [%s]\n", str);
    exit(0);
}

void error_mc()
{
	ft_printf("File not created\n");
	exit(0);
}

void error_null(int y, int x)
{
	ft_printf("Syntax error at [%d:%d] \"null\"\n" ,y + 1, x + 1);
	exit(0);
}
