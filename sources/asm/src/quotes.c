/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:52:18 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/05 19:52:20 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		while_next_space(char *str, int i, t_parser *par)
{
	while (str[i] && str[i] != ' ' && str[i] != '"')
		i++;
	check_name_of_comment(par, str, i);
	if (str[i] == '"')
	{
		par->x += i + 2;
		return (i);
	}
	while (str[i + 1] && str[i] == ' ')
	{
		if (str[i + 1] != ' ')
			break ;
		i++;
	}
	if (str[i] != ' ' || str[++i] != '"')
		error_syntax(par->y, par->x + i);
	par->x += i + 2;
	return (i);
}

int		quotes2(char **str, t_parser *par)
{
	if (!par->file[par->y])
		error_quotes();
	*str = ft_strjoin_free(*str, "\n", 1, 0);
	*str = ft_strjoin_free(*str, par->file[par->y], 1, 0);
	par->x = 1;
	return (1);
}

char	*quotes3(char *str, int *i1, int i, t_parser *par)
{
	par->x = 1;
	*i1 = i;
	return (ft_strjoin_free(str, "\n", 1, 0));
}

char	*quotes(char *str, int *i1, int *j1, t_parser *par)
{
	int i;
	int j;

	i = while_next_space(str, 0, par);
	j = i + 1;
	while (str[j] != '"')
	{
		while (str[j] == '\0')
		{
			par->flag = 1;
			par->y++;
			if (par->file[par->y] && par->file[par->y][0] == '\"')
			{
				*j1 = j + 1;
				return (quotes3(str, &(*i1), i, par));
			}
			j += quotes2(&str, par);
		}
		par->x++;
		j++;
	}
	*i1 = i;
	*j1 = j;
	return (str);
}
