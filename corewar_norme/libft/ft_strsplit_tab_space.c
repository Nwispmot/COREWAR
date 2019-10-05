/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <dmorar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:16:10 by dmorar            #+#    #+#             */
/*   Updated: 2018/12/13 18:35:45 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c, char a)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s[j] != c || s[j] != a)
		i = 1;
	while (s[j] != '\0')
	{
		if ((s[j] == c || s[j] == a) && (s[j + 1] != c || s[j + 1] != a)
		&& s[j + 1] != '\0')
			i++;
		j++;
	}
	return (i);
}

static int		ft_count_letter(char const *s, char c, char a, int l)
{
	int		i;

	if (s[l] == 0)
		return (0);
	i = 0;
	while ((s[l] != c && s[l] != a) && s[l] != '\0')
	{
		i++;
		l++;
	}
	return (i);
}

static void		*free_mysplit(char **str1, int size)
{
	while (size--)
	{
		free(str1[size]);
	}
	free(str1);
	return (NULL);
}

static char		*ft_filler(char *str2, int num, int min, int size)
{
	int		n;
	char	*str1;

	str1 = ft_strnew(num + 1);
	if (!str1)
		return (free_mysplit(&str2, size));
	n = 0;
	while (num--)
	{
		str1[n] = str2[min];
		min++;
		n++;
	}
	str1[n] = '\0';
	return (str1);
}

char			**ft_strsplit_tab_space(char const *s, char c, char a)
{
	char	**new;
	int		i;
	int		size;
	int		l;
	int		len;

	if (s == 0 || c == 0 || a == 0)
		return (0);
	i = 0;
	size = 0;
	len = ft_count_words(s, c, a);
	if (!(new = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	l = 0;
	while (s[l] && i != len)
	{
		while (s[l] == c || s[l] == a)
			l++;
		size = ft_count_letter(s, c, a, l);
		new[i] = ft_filler((char *)s, size, l, len);
		l = size + l;
		i++;
	}
	new[i] = NULL;
	return (new);
}
