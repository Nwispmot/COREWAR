#include "asm.h"

//void	add_label(t_parser *par, char *str, int len)
//{
//	t_label *fresh;
//	t_label *head;
//
//	head = par->labels;
//	if (!par->labels)
//	{
//		par->labels = (t_label*)malloc(sizeof(t_label));
//		par->labels->label = ft_strsub(str, 0, len);
//		par->labels->next = NULL;
//		par->labels->prev = NULL;
//	}
//	else
//	{
//		fresh = (t_label*)malloc(sizeof(t_label));
//		fresh->label = ft_strsub(str, 0, len);
//		fresh->next = NULL;
//
//		while(head->next)
//		{
//			if (ft_strcmp(head->label, fresh->label) == 0)
//			{
//				free(fresh);
//				return ;
//			}
//			head = head->next;
//		}
//		if (ft_strcmp(head->label, fresh->label) == 0)
//		{
//			free(fresh);
//			return ;
//		}
//		fresh->prev = head;
//		head->next = fresh;
//	}
//}

void    add_token(t_parser *par, t_type type, char *content)
{
	t_token	*new;
	t_token	*head;

	if (!par->tokens)
	{
		par->tokens = (t_token*)malloc(sizeof(t_token));
		ft_bzero(par->tokens, sizeof(t_token));
		par->tokens->type = type;
		if (content)
			par->tokens->content = ft_strdup(content);
		par->tokens->next = NULL;
	}
	else
	{
		head = par->tokens;
		while (head->next)
		{
			head = head->next;
		}
		new = (t_token*)malloc(sizeof(t_token));
		ft_bzero(new, sizeof(t_token));
		new->type = type;
		if (content)
			new->content = ft_strdup(content);
		new->next = NULL;
		head->next = new;
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
//		add_label(par, str, len);
		return (1);
	}
	else
		return (0);
}

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
        	add_token(par, OPERATOR, split[i]);
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
	split = ft_strsplit_tab_space(par->file[par->y], ' ', '\t');
	while(flag)
	{
		flag = 0;
		if (is_label(split[i], par))
        {
		    add_token(par, LABEL, split[i]);
		    par->x += ft_strlen(split[i]);
		    i++;
        }
		if (!split[i])
		{
			par->y++;
			par->x = 0;
			if (par->file[par->y] == NULL)
				error_syntax(par->y, par->x);
			flag = 1;
			i = 0;
			split = ft_strsplit_tab_space(par->file[par->y], ' ', '\t');
		}
	}
	is_operation(&split[i], par);
	par->y++;
	add_token(par, NEW_LINE, NULL);
	par->x = 0;
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
	for (int i = 6;parser.tokens;i++)
	{
		if(parser.tokens->type == LABEL)
			ft_printf("%s\n", parser.tokens->content);
		parser.tokens = parser.tokens->next;
	}
	ft_printf("%s\n", parser.file_name);
//	ft_printf("%s", );
	//file_cor(&parser);
	exit(0);
}