/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:07:37 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/10 20:31:10 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		cwidth(t_pf *pf)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < pf->flags[width] - 1)
	{
		if (pf->flags[zero] == 1)
			count += write(1, "0", 1);
		else
			count += write(1, " ", 1);
		i++;
	}
	return (count);
}

void	conv_c(t_pf *pf, va_list ap)
{
	char		c;

	c = (char)va_arg(ap, int);
	if (pf->flags[minus] == 1)
	{
		pf->size += write(1, &c, 1);
		pf->size += cwidth(pf);
	}
	else if (pf->flags[minus] == 0)
	{
		pf->size += cwidth(pf);
		pf->size += write(1, &c, 1);
	}
}

void	conv_s(t_pf *pf, va_list ap)
{
	char *s;
	char *str;
	char *del;

	s = va_arg(ap, char *);
	if (s != NULL)
	{
		str = ft_strnew(ft_strlen(s));
		str = ft_strcpy(str, s);
	}
	if (s == NULL)
		str = ft_strdup("(null)");
	if (pf->flags[prec] != -1)
	{
		del = str;
		str = ft_strsub(str, 0, (size_t)pf->flags[prec]);
		free(del);
	}
	if ((pf->flags[width] != 0) && (pf->flags[width] > (int)ft_strlen(str)))
		str = swidth(pf, str);
	pf->size += ft_strlen(str);
	ft_putstr(str);
	free(str);
}
