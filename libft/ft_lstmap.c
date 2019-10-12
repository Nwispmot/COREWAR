/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <nwispmot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:53:52 by nwispmot          #+#    #+#             */
/*   Updated: 2018/12/29 18:40:57 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del(void *content, size_t contentsize)
{
	free(content);
	contentsize = 0;
	content = NULL;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fresh;
	t_list *new;
	t_list *tmp;

	fresh = NULL;
	new = NULL;
	if (lst && f)
	{
		while (lst)
		{
			tmp = f(lst);
			if (new && (new->next = ft_lstnew(tmp->content, tmp->content_size)))
				new = new->next;
			else if (!new && (new = ft_lstnew(tmp->content, tmp->content_size)))
				fresh = new;
			else
			{
				ft_lstdel(&fresh, &del);
				break ;
			}
			lst = lst->next;
		}
		return (fresh);
	}
	return (NULL);
}
