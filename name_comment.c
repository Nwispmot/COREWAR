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

#include "asm.h"

void	check_file_name(char *str, t_parser *par)
{
	size_t i;

	i = ft_strlen(str) - 1;
	if (str[i] != 's' || str[i - 1] != '.')
		print_error_file();
	par->file_name = ft_strnew(i - 2);
	ft_strncpy(par->file_name, str, i - 1);
	par->file_name = ft_strjoin_free(par->file_name, ".cor", 1, 0);
}

void	quotes(char *str, int *i1, int *j1, t_parser *par)
{
	int i;
	int j;

	i = 0;
	while (str[i] != '"')
		i++;
	j = i + 1;
	par->x += i + 2;
	while (str[j] != '"')
	{
		while (str[j] == '\0')
		{
			par->y++;
			str = ft_strjoin(ft_strjoin(str, "\n"), par->file[par->y]);
			par->x = 1;
			j++;
		}
		par->x++;
		j++;
	}
	*i1 = i;
	*j1 = j;
}

void	new_name_or_commit(char *str, t_parser *par, int be)
{
	int j;
	int i;
	int len;

	i = 0;
	len = -1;
	quotes(str, &i, &j, par);
	len += (j - i);
	if (ft_strncmp(NAME_CMD_STRING, str, 5) == 0)
	{
		len <= PROG_NAME_LENGTH ? 1 : error_longname();
		par->name ? error_syntax(par->y, be) : 1;
		par->name = ft_strsub(str, i + 1, (j - i) - 1);
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, str, 8) == 0)
	{
		len <= COMMENT_LENGTH ? 1 : error_longcomment();
		par->comment ? error_syntax(par->y, be) : 1;
		par->comment = ft_strsub(str, i + 1, (j - i) - 1);
	}
	else
		error_syntax(par->y, par->x);
}

void	parse_name_and_comment(t_parser *par)
{
	int flag;

	flag = 0;
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
			flag = 0;
		}
		else if (par->file[par->y][par->x] == '.' && !flag)
		{
			new_name_or_commit(&par->file[par->y][par->x], par, par->x);
			flag = 1;
		}
		else if (par->name != NULL && par->comment != NULL && !flag)
			break ;
		else
			error_syntax(par->y, par->x);
	}
}

void	check_end_line(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i] != '\0')
		i++;
	while(i > 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0'))
	{
		if(str[i] == '\n')
			j++;
		i--;
	}
	if(j == 0)
		error_endline();
}

void	read_file(t_parser *par)
{
	char	buf[100];
	char	*tmp;
	ssize_t		k;
	char	*file;

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
