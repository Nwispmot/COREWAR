#include "asm.h"

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

void	new_token(t_parser *par)
{
	char 	**split;
	int 	i;
	static int 	j;

	i = 0;
	split = ft_strsplit_tab_space(par->file[par->y], ' ', '\t');
	if (is_label(split[i], par))
		ft_printf("|", ++j);
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
		while (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x]
		== COMMENT_CHAR || par->file[par->y][par->x] == ALT_COMMENT_CHAR)
			par->y++;
		new_token(par);
	}
}

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

	ft_printf("\n");
	for (int i = 1;parser.labels;i++)
	{
		ft_printf("%d %s\n", i, parser.labels->label);
		parser.labels = parser.labels->next;
	}

	exit(0);
}