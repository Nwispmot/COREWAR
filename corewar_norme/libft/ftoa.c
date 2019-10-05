/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:28:37 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 19:28:40 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	beg(t_pf *pf, t_fl *fl)
{
	fl->bval = fl->val;
	fl->i = 0;
	fl->integer = ft_ltoa(fl->val);
	if (fl->val < 0)
		fl->val *= -1;
	if (pf->flags[prec] != -1)
		pf->len = pf->flags[prec] + 1;
	else
		pf->len = 7;
	fl->t = (long long)fl->val;
	fl->val -= fl->t;
	fl->ret = ft_strnew(pf->len);
	fl->ret[0] = '.';
	while (++fl->i < pf->len)
	{
		fl->val *= 10;
		fl->t = (int)fl->val;
		fl->ret[fl->i] = (char)(fl->val + '0');
		fl->val -= fl->t;
	}
	fl->val *= 10;
}

char	*ret_free(t_fl *fl, int f)
{
	char *fresh;

	if (f == 1)
	{
		free(fl->integer);
		fresh = ft_strnew(ft_strlen(fl->ret));
		fresh = ft_strcpy(fresh, fl->ret);
		free(fl->ret);
	}
	if (f == 2)
	{
		free(fl->ret);
		fresh = ft_strnew(ft_strlen(fl->integer));
		fresh = ft_strcpy(fresh, fl->integer);
		free(fl->integer);
	}
	if (f == 3)
	{
		fl->bval > 0 ? fl->bval++ : fl->bval--;
		free(fl->integer);
		free(fl->ret);
		fresh = ft_ltoa(fl->bval);
	}
	free(fl);
	return (fresh);
}

char	*ftoa(t_pf *pf, long double value, int re)
{
	t_fl	*fl;

	fl = (t_fl*)malloc(sizeof(t_fl));
	fl->val = value;
	re++;
	beg(pf, fl);
	if (fl->val >= 5 && re == 0)
	{
		if (fl->ret[fl->i - 1] == '9' && ++re)
			fl->bval = fl->bval >= 0 ? fl->bval + (1 / ft_pow(10, pf->len - 2))
					: fl->bval - (1 / ft_pow(10, pf->len - 2));
		if (pf->flags[prec] == 0)
			return (ret_free(fl, 3));
		fl->ret[fl->i - 1] = (char)(++fl->t + '0');
	}
	fl->ret = ft_strjoin_free(fl->integer, fl->ret, 0, 1);
	if (re == 1)
	{
		free(fl->ret);
		fl->ret = ftoa(pf, fl->bval, re);
	}
	if (pf->len > 1)
		return (ret_free(fl, 1));
	else
		return (ret_free(fl, 2));
}
