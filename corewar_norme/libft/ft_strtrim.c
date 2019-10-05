/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:24:27 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/13 18:40:53 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		p;

	i = 0;
	j = 0;
	p = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		j++;
	}
	while (s[i])
		i++;
	if (j == i)
		return (ft_strnew(0));
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i--;
		p++;
	}
	return (ft_strsub(s, j, (ft_strlen(s) - p - j)));
}
