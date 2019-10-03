/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 21:14:37 by dmorar            #+#    #+#             */
/*   Updated: 2019/10/01 21:14:39 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void	error_param_count(void)
{
	ft_printf("Invalid parameter count\n");
	exit(0);
}

void	error_longname(void)
{
	ft_printf("Champion name too long (Max length 128)\n");
	exit(0);
}

void	error_longcomment(void)
{
	ft_printf("Champion comment too long (Max length 2048)\n");
	exit(0);
}

void	error_name_comment(void)
{
	ft_printf("No name or comment\n");
	exit(0);
}
