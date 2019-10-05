/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:51:37 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/21 16:51:50 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*owidth(t_pf *pf, char *str, intmax_t n)
{
	int		i;
	int		len;
	char	*pre;

	i = -1;
	len = pf->flags[width] - (int)ft_strlen(str);
	pre = ft_strnew(pf->flags[width] - (int)ft_strlen(str));
	while (++i < len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	ocheck(pf, &str, pre, n);
	if (str[0] == '+' && str[1] == '0' && pf->flags[zero] == 1)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	if (pf->flags[minus] == 0)
		return (str = ft_strjoin_free(pre, str, 1, 1));
	else
		return (str = ft_strjoin_free(str, pre, 1, 1));
}

char	*iwidth(t_pf *pf, char *str, intmax_t n)
{
	int		i;
	int		len;
	char	*pre;
	char	*fresh;

	i = -1;
	len = pf->flags[width] - (int)ft_strlen(str);
	pre = ft_strnew(pf->flags[width] - (int)ft_strlen(str));
	while (++i < len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	check(pf, &str, &pre, n);
	if (str[0] == '+' && str[1] == '0' && pf->flags[zero] == 1)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	fresh = pf->flags[minus] == 0 ? ft_strjoin_free(pre, str, 1, 1)
			: ft_strjoin_free(str, pre, 1, 1);
	return (fresh);
}

char	*swidth(t_pf *pf, char *str)
{
	int		i;
	int		len;
	char	*pre;
	char	*fresh;

	i = 0;
	len = pf->flags[width] - (int)ft_strlen(str);
	pre = (char *)malloc((sizeof(char)) * (len + 1));
	fresh = NULL;
	while (i < len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
		i++;
	}
	pre[i] = '\0';
	if (pf->flags[minus] == 0)
		fresh = ft_strjoin_free(pre, str, 1, 1);
	else if (pf->flags[minus] == 1)
		fresh = ft_strjoin_free(str, pre, 1, 1);
	return (fresh);
}

char	*fwidth(t_pf *pf, char *str, intmax_t n)
{
	int		i;
	int		len;
	char	*pre;
	char	*fresh;

	i = -1;
	len = pf->flags[width] - (int)ft_strlen(str);
	pre = ft_strnew(len);
	while (++i < len)
	{
		if (pf->flags[zero] == 1 && str[0] != 'n')
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	check(pf, &str, &pre, n);
	if (str[0] == '+' && str[1] == '0' && pf->flags[zero] == 1)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	pre[i] = '\0';
	fresh = pf->flags[minus] == 0 ? ft_strjoin_free(pre, str, 1, 1)
			: ft_strjoin_free(str, pre, 1, 1);
	return (fresh);
}

char	*uwidth(t_pf *pf, char *str, intmax_t n)
{
	int		i;
	int		len;
	char	*pre;
	char	*fresh;

	i = -1;
	len = pf->flags[width] - (int)ft_strlen(str);
	pre = ft_strnew(pf->flags[width] - (int)ft_strlen(str));
	while (++i < len)
	{
		if (pf->flags[zero] == 1)
			pre[i] = '0';
		else
			pre[i] = ' ';
	}
	ucheck(pf, &str, &pre, n);
	if (str[0] == '+' && str[1] == '0' && pf->flags[zero] == 1)
	{
		pre[0] = '+';
		str[0] = '0';
	}
	fresh = pf->flags[minus] == 0 ? ft_strjoin_free(pre, str, 1, 1)
			: ft_strjoin_free(str, pre, 1, 1);
	return (fresh);
}
