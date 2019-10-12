/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:33 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/19 19:46:16 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *fresh;

	fresh = 0;
	if (!(fresh = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	ft_bzero(fresh, size + 1);
	return (fresh);
}
