/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uhex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:08:08 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/21 20:08:22 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*xminus(t_pf *pf, int n, char *str, char *pre)
{
	if (pf->flags[sharp] == 1 && pf->flags[zero] == 1
		&& n != 0 && ft_strchr(str, pf->convers) == NULL)
	{
		pre[1] = pf->convers;
		str[1] = '0';
	}
	if (pf->flags[sharp] == 1 && pf->flags[zero] == 0 && n != 0
		&& ft_strchr(str, pf->convers) == NULL)
	{
		pre[pf->len - 1] = pf->convers;
		pre[pf->len - 2] = '0';
		str[1] = '0';
	}
	if (pf->flags[sharp] == 1 && pf->flags[zero] == 1 && n != 0)
	{
		if (pf->len > 1)
			pre[1] = pf->convers;
		else
			str[0] = pf->convers;
		if (ft_strchr(str, pf->convers) != NULL)
			str[1] = '0';
	}
	return (ft_strjoin_free(pre, str, 1, 1));
}

char	*uxwidth(t_pf *pf, char *str, int n)
{
	int		i;
	char	*pre;

	i = -1;
	pf->len = pf->flags[width] - (int)ft_strlen(str);
	pre = ft_strnew((sizeof(char)) * pf->len);
	while (++i < pf->len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	if (pf->flags[minus] == 0)
		return (xminus(pf, n, str, pre));
	else
		return (ft_strjoin_free(str, pre, 1, 1));
}

char	*uxprec(t_pf *pf, char *str, int n)
{
	int		len;
	int		i;
	char	*pre;
	char	*fresh;

	i = 0;
	len = pf->flags[prec] - (int)ft_strlen(str);
	pre = (char *)malloc((sizeof(char)) * (len + 1));
	while (i < len)
		pre[i++] = '0';
	pre[i] = '\0';
	if (pf->flags[sharp] == 1 && pf->flags[width] != 0
		&& pf->flags[prec] == -1 && n != 0)
		pre[1] = pf->convers;
	else if (pf->flags[sharp] == 1 && pf->flags[prec] != -1 && n != 0)
		pre = ft_strjoin_free("0X", pre, 0, 1);
	fresh = ft_strjoin_free(pre, str, 1, 1);
	return (fresh);
}

void	uxprint(t_pf *pf, char *str, uintmax_t n)
{
	if (pf->flags[prec] >= (int)(ft_strlen(str)) || (pf->flags[prec] >
	(int)(ft_strlen(str) - 1) && ft_strchr(str, '-') != NULL))
		str = uxprec(pf, str, n);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0')
		str = ft_strdup_free("\0", str);
	if (ft_strchr(str, pf->convers) == NULL && ((pf->flags[sharp] == 1
	&& n != 0 && pf->flags[width] == 0 && pf->flags[prec] != -1) ||
	(pf->flags[sharp] == 1 && n != 0 && pf->flags[width] == 0 &&
	pf->flags[prec] == -1) || (pf->flags[sharp] == 1 && n != 0 &&
	pf->flags[width] != 0 && pf->flags[prec] == -1) ||
	(pf->flags[sharp] == 1 && n != 0 && pf->flags[width] != 0
	&& pf->flags[prec] != -1)))
		str = ft_strjoin_free("0X", str, 0, 1);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = uxwidth(pf, str, n);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}

void	conv_ux(t_pf *pf, va_list ap)
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
	uxprint(pf, str, n);
}
