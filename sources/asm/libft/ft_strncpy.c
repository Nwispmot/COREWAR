/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:56:37 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/10 20:53:40 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	unsigned char	*orig;
	unsigned char	*res;

	orig = (unsigned char *)src;
	res = (unsigned char *)dest;
	while (n && *orig)
	{
		*(res++) = *(orig++);
		n--;
	}
	*(res++) = '\0';
	while (n-- > 0)
		*(res++) = '\0';
	return (dest);
}
