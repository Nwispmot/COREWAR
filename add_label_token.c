/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:21:35 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/29 17:21:38 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void			add_token(t_parser *par, t_type type, char *content)
{
	t_token	*new;

	if (!par->tokens)
	{
		par->tokens = (t_token*)malloc(sizeof(t_token));
		ft_bzero(par->tokens, sizeof(t_token));
		par->tokens->type = type;
		if (content)
			par->tokens->content = ft_strdup(content);
		par->tokens->next = NULL;
		par->head = par->tokens;
	}
	else
	{
		while (par->tokens->next)
			par->tokens = par->tokens->next;
		new = (t_token*)malloc(sizeof(t_token));
		ft_bzero(new, sizeof(t_token));
		new->type = type;
		if (content)
			new->content = ft_strdup(content);
		new->next = NULL;
		par->tokens->next = new;
		par->tokens = par->tokens->next;
	}
}

void			add_label(t_parser *par, t_token *token)
{
	t_label		*new;
	t_label		*head;

	if (!par->labels)
	{
		par->labels = (t_label*)malloc(sizeof(t_label));
		ft_bzero(par->labels, sizeof(t_label));
		par->labels->point = token;
		par->labels->prev = NULL;
		par->labels->next = NULL;
	}
	else
	{
		head = par->labels;
		while (head->next)
			head = head->next;
		new = (t_label*)malloc(sizeof(t_label));
		ft_bzero(new, sizeof(t_label));
		new->point = token;
		new->next = NULL;
		head->next = new;
		new->prev = head;
	}
}

void			add_label_token2(t_parser *par, char *content)
{
	t_token		*new;

	while (par->tokens->next)
		par->tokens = par->tokens->next;
	new = (t_token*)malloc(sizeof(t_token));
	ft_bzero(new, sizeof(t_token));
	new->type = LABEL;
	if (content)
		new->content = ft_strsub(content, 0, ft_strlen(content) - 1);
	new->next = NULL;
	par->tokens->next = new;
	par->tokens = par->tokens->next;
	par->tokens->bytes = g_bytes;
}

void			add_label_token(t_parser *par, char *content)
{
	if (!par->tokens)
	{
		par->tokens = (t_token*)malloc(sizeof(t_token));
		ft_bzero(par->tokens, sizeof(t_token));
		par->tokens->type = LABEL;
		if (content)
			par->tokens->content =
			ft_strsub(content, 0, ft_strlen(content) - 1);
		par->tokens->next = NULL;
		par->head = par->tokens;
		par->tokens->bytes = g_bytes;
	}
	else
		add_label_token2(par, content);
	add_label(par, par->tokens);
}
