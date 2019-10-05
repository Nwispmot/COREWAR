/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:34:47 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/23 17:41:02 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	if (alst == NULL)
		new->next = NULL;
	if (alst && new)
	{
		new->next = (*alst);
		(*alst) = new;
	}
}
