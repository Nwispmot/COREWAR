/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 21:14:00 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/23 23:03:40 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	st(unsigned char *s1, unsigned char *s2, size_t len)
{
	size_t				i;
	size_t				j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i] != s2[j] && i < len && s1[i] != '\0')
			i++;
		while (s1[i] == s2[j] && i < len)
		{
			j++;
			i++;
			if (s2[j] == '\0')
			{
				if (i - j == 0)
					return (1);
				return (0);
			}
		}
	}
	return (0);
}

static int	stn(unsigned char *s1, unsigned char *s2, size_t len)
{
	size_t				i;
	size_t				j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i] != s2[j] && i < len && s1[i] != '\0')
			i++;
		while (s1[i] == s2[j] && i < len)
		{
			j++;
			i++;
			if (s2[j] == '\0')
				return (i - j);
		}
		if (s1[i] == '\0')
			return (0);
		i = i - j;
		j = 0;
		i++;
	}
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t				i;
	unsigned char		*s1;
	unsigned char		*s2;

	s1 = (unsigned char*)haystack;
	s2 = (unsigned char*)needle;
	if (ft_strcmp(haystack, needle) == 0)
		return ((char*)&s1[0]);
	if (*needle == '\0')
		return ((char*)haystack);
	i = st(s1, s2, len);
	if (i == 1)
		return ((char*)&s1[0]);
	i = stn(s1, s2, len);
	if (i != 0)
		return ((char*)&s1[i]);
	return (NULL);
}
