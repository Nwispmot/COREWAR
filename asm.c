#include "asm.h"

void	check_file_name(char *str, t_parser *par)
{
	size_t i;

	i = ft_strlen(str) - 1;
	if (str[i] != 's' || str[i - 1] != '.')
		print_error_file();
	par->file_name = ft_strnew(i - 2);
	ft_strncpy(par->file_name, str, i - 1);
}

void	new_name_or_commit(char *str, t_parser *par) //add name and commit of champ
{
	int j;
	int i;
	int len;

	i = 0;
	len = -1;
	while (str[i] != '"')
		i++;
	j = i + 1;
	par->x += i + 2;
	while (str[j] != '"')
	{
		while (str[j] == '\0')
		{
			par->y++;
			str = ft_strjoin(ft_strjoin(str, "\n"),par->file[par->y]);
			par->x = 1;
			j++;
		}
		par->x++;
		j++;
	}
	len += (j - i);
	if (ft_strncmp(NAME_CMD_STRING, str, 5) == 0 && len <= PROG_NAME_LENGTH && par->name == NULL)
		par->name = ft_strsub(str, i + 1, (j - i) - 1);
	else if (ft_strncmp(COMMENT_CMD_STRING, str, 8) == 0 && len <= COMMENT_LENGTH && par->comment == NULL)
		par->comment = ft_strsub(str, i + 1, (j - i) - 1);
	else
	{
		error_lexical(par->y, par->x);
		exit(0);
	}
}

void	parse_name_and_comment(t_parser *par)
{
	int flag;

	flag = 0;
	while (par->file[par->y] != NULL && (par->name == NULL || par->comment == NULL))
	{
		while ((par->file[par->y][par->x] == ' ' || par->file[par->y][par->x] == '\t') &&
		par->file[par->y][par->x] != '\0')
			par->x++;
		if (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x] == '#')
		{
			par->y++;
			par->x = 0;
			flag = 0;
		}
		else if (par->file[par->y][par->x] == '.' && !flag)
		{
			new_name_or_commit(&par->file[par->y][par->x], par);
			flag = 1;
		}
		else
			error_lexical(par->y, par->x);
	}
	if (par->name == NULL || par->comment == NULL)
		print_error_file();
}



void	read_file(t_parser *par)
{
	char	*line;
	char 	*file;

	file = NULL;
	while (get_next_line(par->fd, &line) > 0)
	{
		if (!file)
		{
			file = ft_strdup(line);
		}
		else
		{
			file = ft_strjoin(file, "\n");
			file = ft_strjoin_free(file, line, 1, 0);
		}
	}
	par->file = ft_strsplit_n(file, '\n');
	free(file);
}
//
//void parse_token(t_parser *par)
//{
//	int flag;
//
//	flag = 0;
//	while (par->file[par->y] != NULL)
//	{
//		while ((par->file[par->y][par->x] == ' ' || par->file[par->y][par->x] == '\t') &&
//			   par->file[par->y][par->x] != '\0')
//			par->x++;
//		if (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x] == '#')
//		{
//			par->y++;
//			par->x = 0;
//			continue ;
//		}
//		else if (par->file[par->y][par->x] == '.')
//		else
//			print_error_file();
//	}
//}

int		main(int ac, char **av)
{
	t_parser parser;

	ft_bzero(&parser, sizeof(t_parser));
	check_file_name(av[1], &parser);
	if (ac == 2)
	{
		ft_printf("Writing output program to %s.cor\n", parser.file_name);
		parser.fd = open(av[1], O_RDONLY);
	}
	read_file(&parser);
	parse_name_and_comment(&parser);
	ft_printf("name ===  \"%s\"\n", parser.name);
	ft_printf("comment ===  \"%s\"", parser.comment);
//	parse_token(&parser);
	exit(0);
}