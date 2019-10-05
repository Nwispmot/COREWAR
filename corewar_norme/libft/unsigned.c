/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:57:43 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/15 18:57:45 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*uprec(t_pf *pf, char *str)
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
		pre[i++] = '0';
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
	fresh = ft_strjoin_free(pre, str, 1, 1);
	return (fresh);
}

void		uprint(t_pf *pf, char *str, uintmax_t n)
{
	if (pf->flags[prec] >= (int)(ft_strlen(str)) ||
	(pf->flags[prec] > (int)(ft_strlen(str) - 1)
	&& ft_strchr(str, '-') != NULL))
		str = uprec(pf, str);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0')
		str[0] = '\0';
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = uwidth(pf, str, n);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}

void		conv_u(t_pf *pf, va_list ap)
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
	str = ft_utoa(n);
	uprint(pf, str, n);
}
