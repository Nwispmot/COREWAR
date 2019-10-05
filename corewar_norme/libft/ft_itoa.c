/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:42:26 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/18 18:54:17 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(intmax_t n)
{
	int size;
	int t;

	size = 0;
	t = 0;
	if (n < 0)
	{
		n *= -1;
		t++;
	}
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size + t);
}

static char	*ma(intmax_t n)
{
	char *fresh;

	fresh = NULL;
	if (n <= -9223372036854775807)
		fresh = (ft_strdup("-9223372036854775808"));
	else if (n >= 9223372036854775807)
		fresh = (ft_strdup("9223372036854775807"));
	return (fresh);
}

char		*ft_itoa(intmax_t n)
{
	char	*fresh;
	int		i;
	int		size;

	if (n <= -9223372036854775807 || n >= 9223372036854775807)
		return (ma(n));
	else
	{
		size = ft_count(n);
		i = size - 1;
		fresh = ft_strnew(size);
		fresh[0] = '-';
		if (n < 0)
		{
			n *= -1;
			size--;
		}
		while (size--)
		{
			fresh[i--] = (char)((n % 10) + '0');
			n = n / 10;
		}
		fresh[size] = '\0';
	}
	return (fresh);
}
