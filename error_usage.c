/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 21:14:25 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/01 21:14:27 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void	error_quotes(void)
{
	ft_printf("No closing quote\n");
	exit(0);
}

void	print_usage(void)
{
	ft_printf("Usage: ./asm <sourcefile.s>\n");
	exit(0);
}

void	error_open(void)
{
	ft_printf("Cannot open file.\n");
	exit(0);
}

void	print_error_file(void)
{
	ft_printf("Invalid file format\n");
	exit(0);
}

void	error_mc(void)
{
	ft_printf("File not created\n");
	exit(0);
}
