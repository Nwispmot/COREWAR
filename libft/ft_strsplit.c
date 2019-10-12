/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:38:43 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/23 23:04:09 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free_array(char **str, int i)
{
	while (i)
		free(str[i--]);
	free(str);
	return (NULL);
}

static int		ft_calc_words(char const *s, char c)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
		if (*s)
			s++;
	}
	return (i);
}

static int		ft_calc_letters(char const *s, char c)
{
	int i;

	while (*s)
	{
		i = 0;
		if (*s != c && *s)
		{
			while (*s != c && *s)
			{
				s++;
				i++;
			}
			return (i);
		}
		if (*s)
			s++;
	}
	return (0);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;

	if (!s || !c)
		return (NULL);
	i = 0;
	str = (char**)malloc(sizeof(str) * (ft_calc_words(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		if (*s != c && *s)
		{
			str[i] = ft_strnew(ft_calc_letters(s, c));
			if (!str[i])
				return (ft_free_array(str, i));
			ft_strncpy(str[i++], s, ft_calc_letters(s, c));
			while (*s != c && *s)
				s++;
		}
		if (*s)
			s++;
	}
	str[i] = NULL;
	return (str);
}
