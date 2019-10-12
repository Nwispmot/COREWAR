/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_sharp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:38:37 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 17:38:39 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_sharp(char *str)
{
	if (str[0] != '0')
		str = ft_strjoin_free("0", str, 0, 1);
	return (str);
}

void	conv_percent(t_pf *pf, va_list ap)
{
	int i;

	ap = NULL;
	i = -1;
	if (pf->flags[width] != 0)
	{
		if (pf->flags[minus] == 1)
			pf->size += write(1, "%", 1);
		while (++i < pf->flags[width] - 1)
		{
			if (pf->flags[zero] == 1)
				pf->size += write(1, "0", 1);
			else
				pf->size += write(1, " ", 1);
		}
	}
	if (pf->flags[minus] != 1)
		pf->size += write(1, "%", 1);
}
