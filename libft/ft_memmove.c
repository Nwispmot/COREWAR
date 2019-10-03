/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:17:58 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/19 19:57:38 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	i = 0;
	if (dst == src)
		return (NULL);
	if (s > d)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
		while (len--)
		{
			*(d + len) = *(s + len);
		}
	return (d);
}
