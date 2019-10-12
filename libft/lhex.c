/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lhex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:04:52 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 18:04:56 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*lxprec(t_pf *pf, char *str, int n)
{
	int		len;
	int		i;
	char	*pre;

	i = 0;
	len = pf->flags[prec] - (int)ft_strlen(str);
	pre = (char*)malloc((sizeof(char)) * (len + 1));
	while (i < len)
	{
		pre[i] = '0';
		i++;
	}
	pre[i] = '\0';
	if (pf->flags[sharp] == 1 && pf->flags[width] != 0 &&
		pf->flags[prec] == -1 && n != 0)
		pre[1] = pf->convers;
	else if (pf->flags[sharp] == 1 && pf->flags[prec] != -1 && n != 0)
		pre = ft_strjoin_free("0x", pre, 0, 1);
	str = ft_strjoin_free(pre, str, 1, 1);
	return (str);
}

void	lxprint(t_pf *pf, char *str, uintmax_t n)
{
	if (pf->flags[prec] >= (int)(ft_strlen(str)) || (pf->flags[prec] >
	(int)(ft_strlen(str) - 1) && ft_strchr(str, '-') != NULL))
		str = lxprec(pf, str, n);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0')
		str = ft_strdup_free("\0", str);
	if ((ft_strchr(str, pf->convers) == NULL) && ((pf->flags[sharp] == 1
	&& n != 0 && pf->flags[width] == 0 && pf->flags[prec] != -1) ||
	(pf->flags[sharp] == 1 && n != 0 && pf->flags[width] == 0 &&
	pf->flags[prec] == -1) || (pf->flags[sharp] == 1 && n != 0 &&
	pf->flags[width] != 0 && pf->flags[prec] == -1) ||
	(pf->flags[sharp] == 1 && n != 0 && pf->flags[width] != 0 &&
	pf->flags[prec] != -1)))
		str = ft_strjoin_free("0x", str, 0, 1);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = uxwidth(pf, str, n);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}

void	conv_lx(t_pf *pf, va_list ap)
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
	str = ft_unsigned_ltoa_base(n, 16, pf->convers - 23);
	lxprint(pf, str, n);
}
