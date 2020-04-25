/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 02:19:09 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/24 02:19:13 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*get_type_f(t_info *info, long double arg)
{
	char		*res;
	char		*left;
	char		*right;
	long double	decimal;
	int			tmp;

	decimal = arg - integer;
	tmp = info->p + 1;
	while (tmp-- > 0)
		decimal *= 10;
	decimal = (decimal + 5) / 10;
	left = max_itoa_base((uint64_t)arg, 10);
	right = max_itoa_base((uint64_t)decimal, 10);
}

void	print_f(t_info *info, char *res, int len, int rest)
{
}

void	put_type_f(t_info *info)
{
	long double	arg;
	char		*res;
	int			len;
	int			rest;

	arg = (info->f & LT_BIGL) ? \
		va_arg(info->ap, long double) : (long double)va_arg(info->ap, double);
	info->f |= (arg < 0) ? CT_SIGN : 0;
	info->p = (info->f & PRECI) ? info->p : 6;
	if (!(res = get_type_f(info, (arg < 0) ? -arg : arg)))
		return ;
	print_f(info, res, len, rest);
	free(res);
}
