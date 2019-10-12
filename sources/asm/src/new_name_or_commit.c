/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_name_or_commit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:25:53 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/05 19:25:56 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	new_name_or_commit2(char **str, t_parser *par)
{
	while ((par->file[par->y][par->x] == ' ' || par->file[par->y][par->x]
	== '\t') && par->file[par->y][par->x] != '\0')
		par->x++;
	if (par->file[par->y][par->x] || par->flag)
		ft_strdel(&(*str));
}

void	new_name_or_commit(char *string, t_parser *par, int be)
{
	int		j;
	int		i;
	int		len;
	char	*str;

	i = 0;
	par->flag = 0;
	len = -1;
	str = quotes(string, &i, &j, par);
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
		error_syntax(par->y, be);
	new_name_or_commit2(&str, par);
}
