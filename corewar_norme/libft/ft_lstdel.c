/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:34:47 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/23 17:42:49 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (alst)
	{
		while ((*alst)->next != NULL)
		{
			tmp = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = NULL;
			(*alst) = tmp;
		}
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
}
