/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:58:34 by nwispmot          #+#    #+#             */
/*   Updated: 2019/03/25 19:58:39 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			nbrbase(const char *str, int base, int res, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * base + str[i] - 48;
		else if (str[i] >= 'A' && str[i] <= 'F')
			res = res * base + str[i] - 55;
		else if (str[i] >= 'a' && str[i] <= 'f')
			res = res * base + str[i] - 87;
		i++;
	}
	return (res);
}

int			ft_atoi_base(const char *str, int base)
{
	int i;
	int res;
	int otr;

	if (!str[0] || (base < 2 || base > 16))
		return (0);
	i = 0;
	res = 0;
	otr = 1;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == '\f'
	|| str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		otr = -1;
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = nbrbase(str, base, res, i);
	return (otr * res);
}
