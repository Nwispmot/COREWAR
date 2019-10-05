/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 20:11:14 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/11 20:48:54 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*s1;
	char				*fresh;

	i = 0;
	if (!s)
		return (0);
	s1 = (char*)s;
	if (!(fresh = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		fresh[i] = f(i, s1[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
