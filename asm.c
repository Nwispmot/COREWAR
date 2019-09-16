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

	i = 0;
	while (str[i] != '"')
		i++;
	j = i + 1;
	while (str[j] != '"')
	{
		if(str[j] == '\0')
		{
			par->y++;
			str = ft_strjoin(str, par->file[par->y]);
		}
		j++;
	}
//	if (str[j] == '\0'|| str[j + 1] != '\0')
//	{
//		ft_printf("empty");
//		exit(0);
//	}
	if (ft_strncmp(NAME_CMD_STRING, str, 5) == 0 && (j - i) - 1 < PROG_NAME_LENGTH)
		par->name = ft_strsub(str, i + 1, (j - i) - 1);
	else if (ft_strncmp(COMMENT_CMD_STRING, str, 8) == 0 && (j - i) - 1 < COMMENT_LENGTH)
		par->comment = ft_strsub(str, i + 1, (j - i) - 1);
	else if (ft_strncmp(NAME_CMD_STRING, str, 5) != 0 && ft_strncmp(COMMENT_CMD_STRING, str, 8) != 0)
	{
		ft_printf("not");
		exit(0);
	}
}

void	parse_asm(t_parser *par)
{

	while (par->file[par->y] != NULL)
	{
		if (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x] == '#')
		{
			par->y++;
			par->x = 0;
			continue ;
		}
		if (par->file[par->y][par->x] == '.')
			new_name_or_commit(&par->file[par->y][par->x], par);
		par->x++;

	}
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
	par->file = ft_strsplit(file, '\n');
	free(file);
}

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
	parse_asm(&parser);
	ft_printf("name ===  \"%s\"\n", parser.name);
	ft_printf("comment ===  \"%s\"", parser.comment);
	exit(0);
}