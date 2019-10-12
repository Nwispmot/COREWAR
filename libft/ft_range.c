/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:44:01 by nwispmot          #+#    #+#             */
/*   Updated: 2018/11/28 22:29:15 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int		i;
	int		dif;
	int		*j;

	if (min >= max)
		return (0);
	dif = max - min;
	i = 0;
	if (!(j = (int*)malloc(dif * sizeof(int))))
		return (NULL);
	while (i < dif)
	{
		j[i] = min;
		min++;
		i++;
	}
	return (j);
}
