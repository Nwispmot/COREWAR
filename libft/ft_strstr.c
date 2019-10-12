/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 21:14:28 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/20 19:40:45 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	stst(unsigned char *s1, unsigned char *s2, int i, int j)
{
	while (s1[i] != '\0')
	{
		while (s1[i] != s2[j])
		{
			if (s1[i] == '\0')
				return (0);
			i++;
		}
		while (s1[i++] == s2[j++])
		{
			if (s2[j] == '\0')
			{
				if (i - j == 0)
					return (-1);
				return (i - j);
			}
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int					i;
	int					j;
	unsigned char		*s1;
	unsigned char		*s2;

	i = 0;
	j = 0;
	s1 = (unsigned char*)haystack;
	s2 = (unsigned char*)needle;
	if (ft_strcmp(haystack, needle) == 0)
		return ((char*)&s1[i]);
	if (*needle == '\0')
		return ((char*)haystack);
	i = stst(s1, s2, i, j);
	if (i == -1)
		return ((char*)&s1[0]);
	if (i != 0)
		return ((char*)&s1[i]);
	return (NULL);
}
