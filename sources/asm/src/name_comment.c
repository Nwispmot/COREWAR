/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:32:29 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/18 18:32:31 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	check_file_name(char *str, t_parser *par)
{
	size_t i;

	i = ft_strlen(str) - 1;
	if (str[i] != 's' || str[i - 1] != '.')
		print_error_file();
	par->file_name = str;
}

void	check_name_of_comment(t_parser *par, char *string, int i)
{
	char *str;

	str = ft_strsub(string, 0, i);
	if (ft_strcmp(str, ".name") != 0 && ft_strcmp(str, ".comment") != 0)
	{
		free(str);
		error_lexical(par->y, par->x + i - 1);
	}
	free(str);
}

void	parse_name_and_comment(t_parser *par)
{
	while (par->file[par->y] != NULL)
	{
		while ((par->file[par->y][par->x] == ' ' || par->file[par->y][par->x]
		== '\t') && par->file[par->y][par->x] != '\0')
			par->x++;
		if (par->file[par->y][par->x] == '\0' || par->file[par->y][par->x]
		== COMMENT_CHAR || par->file[par->y][par->x] == ALT_COMMENT_CHAR)
		{
			par->y++;
			par->x = 0;
			par->flag = 0;
		}
		else if (par->file[par->y][par->x] == '.' && !par->flag)
		{
			new_name_or_commit(&par->file[par->y][par->x], par, par->x);
			par->flag = 1;
		}
		else if (par->name != NULL && par->comment != NULL && !par->flag)
			break ;
		else
			error_syntax(par->y, par->x);
	}
	if (!par->name || !par->comment)
		error_name_comment();
}

void	check_end_line(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
		i++;
	while (i > 0 && (str[i] == ' ' || str[i] == '\t' ||
	str[i] == '\n' || str[i] == '\0'))
	{
		if (str[i] == '\n')
			j++;
		i--;
	}
	if (j == 0)
		error_endline();
}

void	read_file(t_parser *par)
{
	char		buf[100];
	char		*tmp;
	ssize_t		k;
	char		*file;

	file = ft_strnew(0);
	while ((k = read(par->fd, buf, 99)) > 0)
	{
		buf[k] = '\0';
		tmp = file;
		file = ft_strjoin(file, buf);
		free(tmp);
	}
	check_end_line(file);
	par->file = ft_strsplit_n(file, '\n');
	free(file);
}
