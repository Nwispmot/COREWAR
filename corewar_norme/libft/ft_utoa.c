/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:16:20 by nwispmot          #+#    #+#             */
/*   Updated: 2019/04/15 19:16:25 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(unsigned long long int n)
{
	int size;

	size = 0;
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

static char	ft_number(unsigned long long n)
{
	unsigned long long t;

	t = n % 10;
	return ((char)(t + '0'));
}

char		*ft_utoa(unsigned long long int n)
{
	char		*fresh;
	long long	i;
	long long	size;
	int			j;

	j = 0;
	size = ft_count(n);
	i = size - 1;
	if (!(fresh = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	while (j++ < size)
	{
		fresh[i--] = ft_number(n);
		n = n / 10;
	}
	fresh[size] = '\0';
	return (fresh);
}
