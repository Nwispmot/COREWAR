#include "asm.h"

void	add_label(t_parser *par, char *str, int len)
{
	t_label *fresh;
	t_label *head;

	head = par->labels;
	if (!par->labels)
	{
		par->labels = (t_label*)malloc(sizeof(t_label));
		par->labels->label = ft_strsub(str, 0, len);
		par->labels->next = NULL;
		par->labels->prev = NULL;
	}
	else
	{
		fresh = (t_label*)malloc(sizeof(t_label));
		fresh->label = ft_strsub(str, 0, len);
		fresh->next = NULL;

		while(head->next)
		{
			if (ft_strcmp(head->label, fresh->label) == 0)
			{
				free(fresh);
				return ;
			}
			head = head->next;
		}
		if (ft_strcmp(head->label, fresh->label) == 0)
		{
			free(fresh);
			return ;
		}
		fresh->prev = head;
		head->next = fresh;
	}
}

int		is_label(char *str, t_parser *par)
{
	int i;
	int len;

	i = -1;

	if (str[len = (ft_strlen(str) - 1)] == LABEL_CHAR)
	{
		while(++i < len)
			if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
				error_lexical(par->y, i);
		add_label(par, str, len);
		return (1);
	}
	else
		return (0);
}

//void	add_token(t_parser *par)
//{
//	t_token	*new;
//
//	if (!par->tokens)
//	{
//		par->tokens = (t_token*)malloc(sizeof(t_token));
//		par->tokens->next = NULL;
//		par->tokens->prev = NULL;
//	}
//}

void    check_args(char *string, int oper)
{
    char **split;
    int i;
    int len;

    i = 0;
    len = 0;
    split = ft_strsplit(string, SEPARATOR_CHAR);
    while (split[len])
        len++;
    if (len != op[oper].args_num)
        error_param();
}

void    is_operation(char **split, t_parser *par)
{
    int oper;
    int i;

    oper = 0;
    i = 0;
    if(!split)
        error_lexical(par->y, par->x);
    while (op[oper].name != NULL)
    {
        if (ft_strcmp(op[oper].name, split[i]) == 0)
        {
            i++;
            check_args(split[i], oper);
            ft_printf("%s\n", op[oper].name);
            return ;
        }
        oper++;
    }
    error_endline();
}

void	new_token(t_parser *par)
{
	char 	**split;
	int 	i;
	int		flag;

	flag = 1;
	i = 0;
	//add_token();
	split = ft_strsplit_tab_space(par->file[par->y], ' ', '\t');
	while(flag)
	{
		flag = 0;
		if (is_label(split[i], par))
			i++;
		if (!split[i])
		{
			par->y++;
			if (par->file[par->y] == NULL)
				error_syntax(par->y, par->x);
			flag = 1;
			i = 0;
			split = ft_strsplit_tab_space(par->file[par->y], ' ', '\t');
//			parse_token(par);
		}
	}
	is_operation(&split[i], par);
	par->y++;
//	if (!par->file[par->y])
//		error_endline();
}

void parse_token(t_parser *par)
{
	int flag;

	flag = 0;
	while (par->file[par->y] != NULL)
	{
	    while ((par->file[par->y][par->x] == '\t' || par->file[par->y][par->x] == ' ') && par->file[par->y][par->x] != '\0')
	        par->x++;
		while (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x]
		== COMMENT_CHAR || par->file[par->y][par->x] == ALT_COMMENT_CHAR)
			par->y++;
		new_token(par);
	}
}

//void file_cor(t_parser *par)
//{
//	int fd;
//	char *base[4];
//
//	base =
//	if((fd = open(par->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
//		error_endline();
//	if(write(fd, "15", 4) == -1)
//	{
//		close(fd);
//		error_endline();
//	}
//	close(fd);
//}

int		main(int ac, char **av)
{
	t_parser parser;

	ft_bzero(&parser, sizeof(t_parser));
	check_file_name(av[1], &parser);
	if (ac == 2)
	{
		parser.fd = open(av[1], O_RDONLY);
		read_file(&parser);
		parse_name_and_comment(&parser);
		parse_token(&parser);
		ft_printf("Writing output program to %s.cor\n", parser.file_name);
	}
	//INDIR
	ft_printf("\n");
	for (int i = 1;parser.labels;i++)
	{
		ft_printf("%d %s\n", i, parser.labels->label);
		parser.labels = parser.labels->next;
	}
	ft_printf("%s\n", parser.file_name);
//	ft_printf("%s", );
	//file_cor(&parser);
	exit(0);
}