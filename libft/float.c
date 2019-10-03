/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:20:55 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 19:21:00 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fcheck(t_pf *pf, long double n, char *str)
{
	if (n != n)
		str = ft_strdup_free("nan", str);
	if (n == +1 / 0.0)
		str = ft_strdup_free("inf", str);
	if (n == -1 / 0.0)
		str = ft_strdup_free("-inf", str);
	if (pf->flags[plus] == 1 && n > 0)
		str = iplus(str);
	if (pf->flags[plus] == 1 && n == 0)
		str = iplus(str);
	if (pf->flags[space] == 1 && n >= 0)
		str = ft_strjoin_free(" ", str, 0, 1);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = fwidth(pf, str, n);
	return (str);
}

void		conv_f(t_pf *pf, va_list ap)
{
	long double	n;
	char		*str;

	if (pf->flags[L] == 1)
		n = va_arg(ap, long double);
	else
		n = va_arg(ap, double);
	if (pf->flags[prec] == 0)
	{
		str = ftoa(pf, n, -1);
		if (pf->flags[sharp] == 1)
			str = ft_strjoin_free(str, ".", 1, 0);
	}
	else
		str = ftoa(pf, n, -1);
	str = fcheck(pf, n, str);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}
