/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 20:50:21 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/19 19:51:40 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	char *s11;
	char *s22;

	s11 = (char*)s1;
	s22 = (char*)s2;
	if (s1 && s2)
	{
		if (ft_strcmp(s11, s22) == 0)
			return (1);
	}
	return (0);
}
