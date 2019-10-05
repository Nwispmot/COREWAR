/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:17:13 by nwispmot          #+#    #+#             */
/*   Updated: 2019/05/23 19:17:39 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

typedef enum	e_flag
{
	zero = 0,
	sharp = 1,
	minus = 2,
	plus = 3,
	space = 4,
	prec = 5,
	width = 6,
	l = 7,
	ll = 8,
	h = 9,
	hh = 10,
	L = 11

}				t_flag;

typedef struct	s_var
{
	int			flags[13];
	int			size;
	int			len;
	char		convers;
}				t_pf;

typedef struct	s_float
{
	long double	bval;
	long long	t;
	int			i;
	char		*ret;
	char		*integer;
	long double	val;
}				t_fl;

int				ft_printf(char *string, ...);
int				parse(char *str, t_pf *pf);
void			conv_c(t_pf *pf, va_list ap);
void			conv_s(t_pf *pf, va_list ap);
void			conv_di(t_pf *pf, va_list ap);
void			conv_u(t_pf *pf, va_list ap);
void			conv_o(t_pf *pf, va_list ap);
void			conv_lx(t_pf *pf, va_list ap);
char			*iwidth(t_pf *pf, char *str, intmax_t n);
void			conv_ux(t_pf *pf, va_list ap);
char			*swidth(t_pf *pf, char *str);
char			*iplus(char *str);
char			*ft_sharp(char *str);
void			conv_p(t_pf *pf, va_list ap);
void			conv_f(t_pf *pf, va_list ap);
char			*fwidth(t_pf *pf, char *str, intmax_t n);
void			conv_percent(t_pf *pf, va_list ap);
char			*uwidth(t_pf *pf, char *str, intmax_t n);
void			ucheck(t_pf *pf, char **str, char **pre, intmax_t n);
void			check(t_pf *pf, char **str, char **pre, intmax_t n);
char			*owidth(t_pf *pf, char *str, intmax_t n);
void			ocheck(t_pf *pf, char **str, char *pre, intmax_t n);
char			*uxwidth(t_pf *pf, char *str, int n);
char			*ftoa(t_pf *pf, long double value, int re);

#endif
