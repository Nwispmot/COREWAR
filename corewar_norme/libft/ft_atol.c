/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:43:25 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/29 15:43:30 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *str)
{
	int				i;
	int				s;
	long long		nb;

	i = 0;
	nb = 0;
	s = 1;
	while (str[i] == '\t' || str[i] == '\r' ||
	str[i] == '\f' || str[i] == '\v' || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		s = -s;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb * 10 / 10 != nb)
			return ((s == 1) ? -1 : 0);
		nb = 10 * nb + (str[i] - '0');
		i++;
	}
	return (nb * s);
}
