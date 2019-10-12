/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 21:16:02 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/01 21:16:04 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	error_syntax(int y, int x)
{
	ft_printf("Syntax error at [%d:%d]\n", y + 1, x + 1);
	exit(0);
}

void	error_endline(void)
{
	ft_printf("Syntax error - unexpected end of input \
	(Perhaps you forgot to end with a newline ?)\n");
	exit(0);
}

void	error_no_label(char *str)
{
	ft_printf("No such label at [%s]\n", str);
	exit(0);
}

void	error_null(int y, int x)
{
	ft_printf("Syntax error at [%d:%d] \"null\"\n", y + 1, x + 1);
	exit(0);
}

void	error_lexical(int y, int x)
{
	ft_printf("Lexical error at [%d:%d]\n", y + 1, x + 1);
	exit(0);
}
