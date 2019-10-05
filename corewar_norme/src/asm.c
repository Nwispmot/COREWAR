/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:01:44 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/24 14:01:48 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	parse_args2(t_parser *par, int i)
{
	while (par->file[par->y][i] && (par->file[par->y][i] == ' ' ||
	par->file[par->y][i] == '\t'))
		i++;
	if (par->file[par->y][i] != '\0')
		error_lexical(par->y, par->x);
	par->x = 0;
	par->y++;
	add_token(par, NEW_LINE, NULL);
}

void	param_count(t_parser *par, int args, int *i)
{
	if (args != g_op[par->oper].args_num)
		error_param_count();
	(*i)--;
}

void	parse_args(t_parser *par, int i)
{
	char	*string;
	int		args;

	args = 0;
	while (par->file[par->y][par->x] != '\0')
	{
		if (par->file[par->y][par->x] == '#')
			return ;
		if (args >= g_op[par->oper].args_num)
			break ;
		while (par->file[par->y][i] != SEPARATOR_CHAR && par->file[par->y][i]
		!= ' ' && par->file[par->y][i] != '\t' && par->file[par->y][i])
			i++;
		string = ft_strsub(par->file[par->y], par->x, i - par->x);
		check_args(string, par);
		args++;
		i++;
		while (par->file[par->y][i] && (par->file[par->y][i] == ' ' ||
		par->file[par->y][i] == '\t'))
			i++;
		par->x = i;
		ft_strdel(&string);
	}
	param_count(par, args, &i);
	parse_args2(par, i);
}

void	parse_token(t_parser *par)
{
	if (!par->file[par->y])
		error_null(par->y, par->x);
	while (par->file[par->y] != NULL)
	{
		while (par->file[par->y] && (par->file[par->y][par->x] == '\0' ||
		par->file[par->y][par->x]
		== COMMENT_CHAR || par->file[par->y][par->x] == ALT_COMMENT_CHAR))
		{
			par->y++;
			par->x = 0;
		}
		if (par->file[par->y])
			new_token(par);
	}
}

int		main(int ac, char **av)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(t_parser));
	g_bytes = 0;
	if (ac == 2)
	{
		check_file_name(av[1], &parser);
		if ((parser.fd = open(av[1], O_RDONLY)) == -1)
			error_open();
		read_file(&parser);
		parse_name_and_comment(&parser);
		parse_token(&parser);
		parser.tokens = parser.head;
		bytes_in_labels(&parser);
		parser.tokens = parser.head;
		fill_and_create(&parser);
	}
	else
		print_usage();
	exit(0);
}
