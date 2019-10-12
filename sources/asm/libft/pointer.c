/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:12:28 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 17:12:31 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pminus(t_pf *pf, char *str, char *pre)
{
	if (pf->flags[zero] == 1 && ft_strchr(str, 'x') == NULL)
	{
		pre[1] = 'x';
		str[1] = '0';
	}
	if (pf->flags[zero] == 0 && ft_strchr(str, 'x') == NULL)
	{
		pre[pf->len - 1] = 'x';
		pre[pf->len - 2] = '0';
		str[1] = '0';
	}
	if (pf->flags[zero] == 1)
	{
		if (pf->len > 1)
			pre[1] = 'x';
		else
			str[0] = 'x';
		if (ft_strchr(str, 'x') != NULL)
			str[1] = '0';
	}
	return (ft_strjoin_free(pre, str, 1, 1));
}

char	*pwidth(t_pf *pf, char *str)
{
	int		i;
	char	*pre;

	i = -1;
	pf->len = pf->flags[width] - (int)ft_strlen(str);
	pre = ft_strnew(pf->len);
	while (++i < pf->len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	if (pf->flags[minus] == 0)
		return (pminus(pf, str, pre));
	else
		return (ft_strjoin_free(str, pre, 1, 1));
}

char	*pprec(t_pf *pf, char *str, void *n)
{
	int		len;
	int		i;
	char	*pre;

	i = 0;
	len = pf->flags[prec] - (int)ft_strlen(str);
	pre = (char *)malloc((sizeof(char)) * (len + 1));
	while (i < len)
	{
		pre[i] = '0';
		i++;
	}
	pre[i] = '\0';
	if (pf->flags[width] != 0 && pf->flags[prec] == -1)
		pre[1] = 'x';
	else if (pf->flags[prec] != -1 && n != 0)
		pre = ft_strjoin_free("0x", pre, 0, 1);
	str = ft_strjoin_free(pre, str, 1, 1);
	return (str);
}

void	conv_p(t_pf *pf, va_list ap)
{
	void	*n;
	char	*str;

	n = va_arg(ap, void *);
	str = ft_unsigned_ltoa_base((unsigned long long)n, 16, 'a');
	if (pf->flags[prec] >= (int)(ft_strlen(str)) || (pf->flags[prec] >
	(int)(ft_strlen(str) - 1) && ft_strchr(str, '-') != NULL))
		str = pprec(pf, str, n);
	else if (pf->flags[prec] == 0 && str[0] == '0' && str[1] == '\0')
		str = ft_strdup_free("\0", str);
	if ((ft_strchr(str, 'x') == NULL) && ((pf->flags[width] == 0 &&
	pf->flags[prec] != -1) || (pf->flags[width] == 0 && pf->flags[prec] == -1)
	|| (pf->flags[width] != 0 && pf->flags[prec] == -1) || (pf->flags[width]
	!= 0 && pf->flags[prec] != -1)))
		str = ft_strjoin_free("0x", str, 0, 1);
	if (pf->flags[width] != 0 && (pf->flags[width] > (int)ft_strlen(str)))
		str = pwidth(pf, str);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}
