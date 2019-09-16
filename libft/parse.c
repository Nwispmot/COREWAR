/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:16:00 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/05 18:16:04 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	addflag(t_pf *pf, char *str, int i)
{
	if (str[i] == ' ')
		pf->flags[space] = 1;
	if (str[i] == '#')
		pf->flags[sharp] = 1;
	if (str[i] == '-')
		pf->flags[minus] = 1;
	if (str[i] == '+')
		pf->flags[plus] = 1;
	if (str[i] == '0')
		pf->flags[zero] = 1;
	i++;
	return (i);
}

int	addprec(t_pf *pf, char *str, int i)
{
	if (ft_isalnum(str[i]) == 0)
		pf->flags[prec] = 0;
	else
		pf->flags[prec] = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]) == 1)
		i++;
	return (i);
}

int	addwidth(t_pf *pf, char *str, int i)
{
	pf->flags[width] = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]) == 1)
		i++;
	return (i);
}

int	addmod(t_pf *pf, char *str, int i)
{
	pf->flags[ll] = 0;
	pf->flags[l] = 0;
	pf->flags[h] = 0;
	pf->flags[hh] = 0;
	pf->flags[L] = 0;
	if (str[i] == 'l' && str[i + 1] == 'l')
	{
		pf->flags[ll] = 1;
		i++;
	}
	else if (str[i] == 'l' && str[i + 1] != 'l')
		pf->flags[l] = 1;
	else if (str[i] == 'h' && str[i + 1] == 'h')
	{
		pf->flags[hh] = 1;
		i++;
	}
	else if (str[i] == 'h' && str[i + 1] != 'h')
		pf->flags[h] = 1;
	else if (str[i] == 'L')
		pf->flags[L] = 1;
	i++;
	return (i);
}

int	parse(char *str, t_pf *pf)
{
	int i;

	i = 1;
	while (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == '+'
	|| str[i] == ' ' || str[i] == 'l' || str[i] == 'L' || str[i] == 'h' ||
	str[i] == '.' || (str[i] >= 49 && str[i] <= 57))
	{
		if (str[i] == '#' || str[i] == '0' || str[i] == '-' ||
		str[i] == '+' || str[i] == ' ')
			i = addflag(pf, str, i);
		if (str[i] == '.')
			i = addprec(pf, str, i + 1);
		if (str[i] >= 49 && str[i] <= 57)
			i = addwidth(pf, str, i);
		if (str[i] == 'l' || str[i] == 'L' || str[i] == 'h')
			i = addmod(pf, str, i);
	}
	if ((pf->flags[prec] != -1 && str[i] != 'f' && str[i] != 'c' &&
	str[i] != 's' && str[i] != '%') || (pf->flags[minus] == 1))
		pf->flags[zero] = 0;
	if (pf->flags[plus] == 1)
		pf->flags[space] = 0;
	pf->convers = str[i];
	return (++i);
}
