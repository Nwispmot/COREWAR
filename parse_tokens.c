/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:18:20 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/29 17:18:22 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

int		is_label(char *str, t_parser *par)
{
	int i;
	int len;

	i = -1;
	if (str[len = (ft_strlen(str) - 1)] == LABEL_CHAR)
	{
		while (++i < len)
			if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
				error_lexical(par->y, i);
		return (1);
	}
	else
		return (0);
}

char	*check_oper(char *string, int *or)
{
	char	*str;
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	while (string[++i])
	{
		if (string[i] == '%')
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
	{
		str = ft_strnew(i);
		ft_strncpy(str, string, i);
		*or -= (ft_strlen(string) - ft_strlen(str));
	}
	else
		str = ft_strdup(string);
	return (str);
}

int		is_operation(char *string, t_parser *par, int i)
{
	int		oper;
	char	*str;

	str = check_oper(string, &i);
	oper = 0;
	if (!str)
		error_lexical(par->y, par->x);
	while (g_op[oper].name != NULL)
	{
		if (ft_strcmp(g_op[oper].name, str) == 0)
		{
			add_token(par, OPERATOR, str);
			par->tokens->data = oper;
			par->oper = oper;
			par->arg = 0;
			par->tokens->bytes = g_bytes;
			g_bytes += 1 + (g_op[par->oper].args_types_code ? 1 : 0);
			ft_strdel(&str);
			return (i);
		}
		oper++;
	}
	ft_strdel(&str);
	error_lexical(par->y, par->x);
	return (0);
}

int		label_or_comand(char *str, t_parser *par, int *i)
{
	if (is_label(str, par))
	{
		add_label_token(par, str);
		return (1);
	}
	else
	{
		*i = is_operation(str, par, *i);
		return (0);
	}
}

void	new_token(t_parser *par)
{
	char	*string;
	int		i;
	int		flag;
	int		label;

	label = 0;
	flag = 1;
	while ((par->file[par->y][par->x] == '\t' || par->file[par->y][par->x]
		== ' ') && par->file[par->y][par->x] != '\0')
		par->x++;
	i = par->x;
	if (par->file[par->y][par->x] == '\0')
		return ;
	while (flag)
	{
		while (par->file[par->y + 1] && (!par->file[par->y][par->x] ||
		par->file[par->y][par->x] == COMMENT_CHAR || par->file[par->y][par->x]
		== ALT_COMMENT_CHAR))
		{
			par->y++;
			par->x = 0;
			while ((par->file[par->y][par->x] == '\t' || par->file[par->y]
			[par->x] == ' ') && par->file[par->y][par->x] != '\0')
				par->x++;
			i = par->x;
			label = 0;
		}
		if (!par->file[par->y][par->x])
			return ;
		while (par->file[par->y][i] != ' ' && par->file[par->y][i] != '\t'
		&& par->file[par->y][i])
			i++;
		string = ft_strsub(par->file[par->y], par->x, i - par->x);
		(flag = label_or_comand(string, par, &i)) == 1 ? label++ : 0;
		label > 1 ? flag = 0 : flag;
		while ((par->file[par->y][i] == ' ' || par->file[par->y][i] == '\t')
		&& par->file[par->y][i])
			i++;
		par->x = i;
		ft_strdel(&string);
	}
	parse_args(par, par->x);
}
