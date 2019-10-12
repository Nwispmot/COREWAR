/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:01:27 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/06 19:09:24 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	long long int	nb;

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
