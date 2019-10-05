/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:39:11 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/20 19:39:14 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ocheck(t_pf *pf, char **str, char *pre, intmax_t n)
{
	if (ft_strchr(*str, '-') != NULL && pf->flags[zero] == 1)
	{
		pre[0] = '-';
		*str[0] = '0';
	}
	if (*str[0] == ' ' && pre[0] == '0')
	{
		pre[0] = ' ';
		*str[0] = '0';
	}
	if (ft_strchr(*str, '+') != NULL && n != 0 && pf->flags[zero] == 1)
	{
		pre[0] = '+';
		*str[0] = '0';
	}
}

char	*oprec(t_pf *pf, char *str)
{
	int		len;
	int		i;
	char	*pre;

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
	if (ft_strchr(str, '-') != NULL)
	{
		pre[0] = '-';
		str[0] = '0';
	}
	if (ft_strchr(str, '+') != NULL)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	return (ft_strjoin_free(pre, str, 1, 1));
}

void	oprint(t_pf *pf, char *str, uintmax_t n)
{
	if (pf->flags[sharp] == 1)
		str = ft_sharp(str);
	if (pf->flags[prec] >= (int)(ft_strlen(str)) || (pf->flags[prec] >
	(int)(ft_strlen(str) - 1) && ft_strchr(str, '-') != NULL))
		str = oprec(pf, str);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0'
	&& pf->flags[sharp] == 0)
		str = ft_strdup_free("\0", str);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = owidth(pf, str, n);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}

void	conv_o(t_pf *pf, va_list ap)
{
	uintmax_t	n;
	char		*str;

	if (pf->flags[l] == 1)
		n = va_arg(ap, unsigned long int);
	else if (pf->flags[ll] == 1)
		n = va_arg(ap, unsigned long long int);
	else
		n = va_arg(ap, unsigned int);
	if (pf->flags[h] == 1)
		n = (unsigned short int)n;
	if (pf->flags[hh] == 1)
		n = (unsigned char)n;
	str = ft_unsigned_ltoa_base(n, 8, 0);
	oprint(pf, str, n);
}
