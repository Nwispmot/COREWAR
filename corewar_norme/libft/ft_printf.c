/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:17:43 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/23 19:17:45 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init(t_pf *pf)
{
	int i;

	i = 0;
	pf->flags[12] = '\0';
	while (i < 13)
	{
		pf->flags[i] = 0;
		i++;
	}
	pf->flags[prec] = -1;
}

void	conversion(t_pf *pf, va_list ap)
{
	if (pf->convers == 'd' || pf->convers == 'i')
		conv_di(pf, ap);
	else if (pf->convers == 's')
		conv_s(pf, ap);
	else if (pf->convers == 'c')
		conv_c(pf, ap);
	else if (pf->convers == 'u')
		conv_u(pf, ap);
	else if (pf->convers == 'o')
		conv_o(pf, ap);
	else if (pf->convers == 'x')
		conv_lx(pf, ap);
	else if (pf->convers == 'X')
		conv_ux(pf, ap);
	else if (pf->convers == '%')
		conv_percent(pf, ap);
	else if (pf->convers == 'p')
		conv_p(pf, ap);
	else if (pf->convers == 'f')
		conv_f(pf, ap);
	else
		pf->size += write(1, &pf->convers, 1);
}

void	val(t_pf *pf, va_list ap, char *string)
{
	int i;

	i = -1;
	while (string[++i])
	{
		if (string[i] == '%')
		{
			init(pf);
			i += parse(&string[i], pf);
			conversion(pf, ap);
			if (string[i] == '\0')
				break ;
			pf->size++;
		}
		else
			pf->size++;
		if (string[i] != '%')
			write(1, &string[i], 1);
		else
		{
			i--;
			pf->size--;
		}
	}
}

int		ft_printf(char *string, ...)
{
	va_list	ap;
	t_pf	*pf;
	int		size;

	pf = (t_pf*)malloc(sizeof(t_pf));
	pf->size = 0;
	va_start(ap, string);
	val(pf, ap, string);
	va_end(ap);
	size = pf->size;
	free(pf);
	return (size);
}
