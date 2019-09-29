/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:14:30 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/29 17:14:33 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned    add_bytes(t_token *operator, char *label, t_parser *par)
{
	unsigned cur_byte;
	unsigned label_byte;
	t_label *head;

	head = par->labels;
	cur_byte = operator->bytes;

	while (head->next)
	{
		if (ft_strcmp(label, head->point->content) == 0)
			break;
		head = head->next;
	}
	while (head->point->next->type != OPERATOR)
		head->point = head->point->next;
	label_byte = head->point->next->bytes;
	return (label_byte - cur_byte);
}

void    bytes_in_labels(t_parser *par)
{
	t_token *operator;

	operator = NULL;
	while (par->tokens)
	{
		if (par->tokens->type == OPERATOR)
			operator = par->tokens;
		else if (par->tokens->type == INDIRECT_LABEL || par->tokens->type == DIRECT_LABEL)
		{
			search_label(par, par->tokens->content);
			par->tokens->data = add_bytes(operator, par->tokens->content, par);
		}
		par->tokens = par->tokens->next;
	}
}

void file_cor(t_parser *par)
{
	int fd;
	char *name;

	name = ft_strsub(par->file_name, 0, ft_strlen(par->file_name) - 2);
	name = ft_strjoin_free(name, ".cor", 1, 0);
	if((fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		error_mc();
	if(write(fd, g_buf, EXEC_START + g_bytes) == -1)
	{
		free(name);
		close(fd);
		error_mc();
	}
	free(name);
	close(fd);
}