/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:35:29 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/22 21:35:31 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	calc_letter(unsigned long value, int base)
{
	int i;

	i = 0;
	if (value <= 0)
		i++;
	while (value > 0)
	{
		value /= base;
		i++;
	}
	return (i);
}

char		*ft_unsigned_ltoa_base(unsigned long long value,
		int base, char c)
{
	char	*num;
	int		len;

	len = calc_letter(value, base);
	num = malloc(sizeof(char) * (len + 1));
	num[len] = '\0';
	if (value == 0)
		num[0] = '0';
	while (value > 0)
	{
		if (value % base < 10)
			num[--len] = value % base + '0';
		else
			num[--len] = value % base + c - 10;
		value /= base;
	}
	return (num);
}
