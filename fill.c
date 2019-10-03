/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:58:21 by nwispmot          #+#    #+#             */
/*   Updated: 2019/09/29 16:58:23 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void	int_to_hex(int32_t dec, int dir_size, unsigned place)
{
	int move;

	move = 0;
	while (dir_size)
	{
		g_buf[place + dir_size - 1] = (u_int8_t)((dec >> move) & 0xFF);
		move += 8;
		dir_size--;
	}
}

void	code_of_args_type(t_token *op, unsigned dest, u_int8_t n_arg)
{
	int8_t	res;
	int		arg;

	res = 0;
	arg = 0;
	while (arg < n_arg)
	{
		if (op->type == REGISTER)
			res |= 1 << 2 * (3 - arg++);
		else if (op->type == DIRECT || op->type == DIRECT_LABEL)
			res |= 2 << 2 * (3 - arg++);
		else if (op->type == INDIRECT || op->type == INDIRECT_LABEL)
			res |= 3 << 2 * (3 - arg++);
		op = op->next;
	}
	int_to_hex(res, 1, dest);
}

void	fill_args_data(t_parser *par, unsigned *dest)
{
	int	len;

	len = 0;
	if (par->head->type == REGISTER)
		len = T_REG;
	else if (par->head->type == DIRECT || par->head->type == DIRECT_LABEL)
		len = g_op[par->oper].t_dir_size;
	else if (par->head->type == INDIRECT || par->head->type == INDIRECT_LABEL)
		len = 2;
	int_to_hex(par->head->data, len, *dest);
	*dest += len;
	par->head = par->head->next;
}

void	filler_char_array(t_parser *par, unsigned dest)
{
	while (par->head)
	{
		if (par->head->type == OPERATOR)
		{
			par->oper = par->head->data;
			int_to_hex(g_op[par->head->data].code, 1, dest);
			dest++;
			if (g_op[par->head->data].args_types_code)
			{
				code_of_args_type(par->head, dest, g_op[par->oper].args_num);
				dest++;
			}
			par->head = par->head->next;
		}
		else if (par->head->type == REGISTER || par->head->type == DIRECT ||
		par->head->type == INDIRECT || par->head->type == DIRECT_LABEL ||
		par->head->type == INDIRECT_LABEL)
			fill_args_data(par, &dest);
		else
			par->head = par->head->next;
	}
}

void	fill_and_create(t_parser *parser)
{
	ft_printf("Writing output program to %s\n", parser->file_name);
	g_buf = (char *)malloc(sizeof(char) * (EXEC_START + g_bytes));
	ft_bzero(g_buf, (EXEC_START + g_bytes));
	int_to_hex(COREWAR_EXEC_MAGIC, 4, 0);
	ft_memcpy(&g_buf[4], parser->name, ft_strlen(parser->name));
	ft_memcpy(&g_buf[4 + PROG_NAME_LENGTH + 4 + 4], parser->comment,
			ft_strlen(parser->comment));
	int_to_hex(g_bytes, 4, (unsigned)(4 + PROG_NAME_LENGTH + 4));
	filler_char_array(parser, EXEC_START);
	file_cor(parser);
	ft_strdel(&g_buf);
}
