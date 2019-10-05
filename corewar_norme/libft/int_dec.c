/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_dec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:05:56 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/10 20:05:58 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*iplus(char *str)
{
	str = ft_strjoin_free("+", str, 0, 1);
	return (str);
}

void	icheck(char **str, char *pre)
{
	if (ft_strchr(*str, '-') != NULL)
	{
		pre[0] = '-';
		*str[0] = '0';
	}
	if (ft_strchr(*str, '+') != NULL)
	{
		pre[0] = '+';
		*str[0] = '0';
	}
}

char	*iprec(t_pf *pf, char *str)
{
	int		len;
	int		i;
	char	*pre;
	char	*fresh;

	i = 0;
	len = pf->flags[prec] - (int)ft_strlen(str);
	if (ft_strchr(str, '-') != NULL || ft_strchr(str, '+') != NULL)
		len++;
	pre = ft_strnew(len);
	while (i < len)
	{
		pre[i] = '0';
		i++;
	}
	icheck(&str, pre);
	fresh = ft_strjoin_free(pre, str, 1, 1);
	return (fresh);
}

void	diprint(t_pf *pf, char *str, intmax_t n)
{
	if (pf->flags[plus] == 1 && n > 0)
		str = iplus(str);
	if (pf->flags[prec] >= (int)(ft_strlen(str)) || (pf->flags[prec] >
	(int)(ft_strlen(str) - 1) && ft_strchr(str, '-') != NULL))
		str = iprec(pf, str);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0')
		str[0] = '\0';
	if (pf->flags[plus] == 1 && n == 0)
		str = iplus(str);
	if (pf->flags[space] == 1 && n >= 0)
		str = ft_strjoin_free(" ", str, 0, 1);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = iwidth(pf, str, n);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}

void	conv_di(t_pf *pf, va_list ap)
{
	intmax_t	n;
	char		*str;

	if (pf->flags[l] == 1)
		n = va_arg(ap, long int);
	else if (pf->flags[ll] == 1)
		n = va_arg(ap, long long int);
	else
		n = va_arg(ap, int);
	if (pf->flags[h] == 1)
		n = (short int)n;
	if (pf->flags[hh] == 1)
		n = (signed char)n;
	str = ft_ltoa(n);
	diprint(pf, str, n);
}
