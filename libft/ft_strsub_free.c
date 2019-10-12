/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:44:27 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/29 18:44:31 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*fresh;

	i = 0;
	if (len == (size_t)(-1))
		return (NULL);
	if (!(fresh = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (!s)
	{
		free(&s);
		return (0);
	}
	while (i < len)
	{
		fresh[i] = s[start];
		i++;
		start++;
	}
	fresh[i] = '\0';
	free(&s);
	return (fresh);
}
