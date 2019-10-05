/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:18:21 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/05 19:18:23 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int			new_token2(t_parser *par, int i)
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
	}
	return (i);
}

void		new_token3(t_parser *par, int *i, int *flag, int *label)
{
	char	*string;

	while (par->file[par->y][*i] != ' ' && par->file[par->y][*i] != '\t'
	&& par->file[par->y][*i])
		(*i)++;
	string = ft_strsub(par->file[par->y], par->x, (*i) - par->x);
	(*flag = label_or_comand(string, par, &(*i))) == 1 ? (*label)++ : 0;
	*label > 1 ? *flag = 0 : *flag;
	while ((par->file[par->y][*i] == ' ' || par->file[par->y][*i] == '\t')
	&& par->file[par->y][*i])
		(*i)++;
	ft_strdel(&string);
}

void		new_token(t_parser *par)
{
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
		i = new_token2(par, i);
		label = 0;
		if (!par->file[par->y][par->x])
			return ;
		new_token3(par, &i, &flag, &label);
		par->x = i;
	}
	parse_args(par, par->x);
}
