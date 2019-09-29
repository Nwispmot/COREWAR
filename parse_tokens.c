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

#include "asm.h"

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
		return (1);
	}
	else
		return (0);
}

void    is_operation(char *str, t_parser *par)
{
	int oper;

	oper = 0;
	if(!str)
		error_lexical(par->y, par->x);
	while (op[oper].name != NULL)
	{
		if (ft_strcmp(op[oper].name, str) == 0)
		{
			add_token(par, OPERATOR, str);
			par->tokens->data = oper; /////////////////////////////////////////////////
			par->oper = oper;
			par->arg = 0;
			par->tokens->bytes = g_bytes;
			g_bytes += 1 + (op[par->oper].args_types_code ? 1 : 0);
			//ft_printf("%s\n", op[oper].name);
			return ;
		}
		oper++;
	}
	error_lexical(par->y, par->x);
}

int    label_or_comand(char *str, t_parser *par)
{
	if (is_label(str, par))
	{
		add_label_token(par, str);
		return (1);
	}
	else
	{
		is_operation(str, par);
		return (0);
	}
}

void	new_token(t_parser *par)
{
	char	*string;
	int		i;
	int		flag;
	int     label;

	label = 0;
	flag = 1;
	while ((par->file[par->y][par->x] == '\t' || par->file[par->y][par->x] == ' ') && par->file[par->y][par->x] != '\0')
		par->x++;
	i = par->x;
	if (par->file[par->y][par->x] == '\0')
		return ;
	while(flag)
	{
		while (par->file[par->y + 1] && (!par->file[par->y][par->x] || par->file[par->y][par->x]
		== COMMENT_CHAR || par->file[par->y][par->x] == ALT_COMMENT_CHAR))
		{
			par->y++;
			par->x = 0;
			while ((par->file[par->y][par->x] == '\t' || par->file[par->y][par->x] == ' ') && par->file[par->y][par->x] != '\0')
				par->x++;
			i = par->x;
			label = 0;
		}
		if (!par->file[par->y][par->x])
			return ;
		while (par->file[par->y][i] != ' ' && par->file[par->y][i] != '\t' && par->file[par->y][i])
			i++;
		string = ft_strsub(par->file[par->y], par->x, i - par->x);
		(flag = label_or_comand(string, par)) == 1 ? label++ : 0;
		label > 1 ? flag = 0 : flag;
		while ((par->file[par->y][i] == ' ' || par->file[par->y][i] == '\t') && par->file[par->y][i])
			i++;
		par->x = i;
		ft_strdel(&string);
	}
	parse_args(par);
}