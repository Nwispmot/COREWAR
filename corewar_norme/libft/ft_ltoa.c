/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:36:13 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 21:36:17 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	calc_len(long long a)
{
	int		i;

	i = 0;
	if (a <= 0)
		i++;
	while (a != 0)
	{
		a /= 10;
		i++;
	}
	return (i);
}

char		*ft_ltoa(long long n)
{
	char	*res;
	int		len;

	len = calc_len(n);
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[--len] = n % 10 + '0';
	while (n > 0)
	{
		res[len--] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
