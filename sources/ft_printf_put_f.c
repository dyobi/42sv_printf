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

char	*get_char_f(t_info *info, char *left, char *right)
{
	char	*res;
	int		index;
	int		tmp;

	index = 0;
	if (!(res = ft_strnew(!(info->p) ? \
		ft_strlen(left) : ft_strlen(left) + info->p + 1)))
		return (NULL);
	while (*left)
		res[index++] = *(left++);
	if (info->p)
	{
		res[index++] = 46;
		tmp = ((int)ft_strlen(right) > info->p) ? 1 : 0;
		while (right[tmp])
			res[index++] = right[tmp++];
		while (tmp++ < info->p)
			res[index++] = 48;
	}
	return (res);
}

char	*get_type_f(t_info *info, long double arg)
{
	char		*res;
	char		*left;
	char		*right;
	long double	decimal;
	int			tmp;

	decimal = arg - (uint64_t)arg;
	tmp = info->p + 1;
	while (tmp-- > 0)
		decimal *= 10;
	decimal = (decimal + 5) / 10;
	right = max_itoa_base((uint64_t)decimal, 10);
	left = max_itoa_base((uint64_t)(((int)ft_strlen(right) > info->p && \
		info->p) || (!(info->p) && right[0] == 49) ? arg + 1 : arg), 10);
	res = get_char_f(info, left, right);
	free(left);
	free(right);
	return (res);
}

void	print_f(t_info *info, char *res, int rest)
{
	(info->f & F_SPACE) ? put_tok(32, 1) : 0;
	(!(info->f & F_MINUS) && !(info->f & F_ZERO)) ? put_tok(32, rest) : 0;
	(!(info->f & F_MINUS) && info->f & F_ZERO) ? put_tok(48, rest) : 0;
	(info->f & CT_SIGN) ? put_tok(45, 1) : 0;
	(info->f & F_PLUS) ? put_tok(43, 1) : 0;
	while (*res)
		ft_putchar_fd(*(res++), 1);
	(info->f & F_MINUS) ? put_tok(32, rest) : 0;
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
	info->f &= (info->f & CT_SIGN) ? (~F_PLUS & ~F_SPACE) : 524287;
	info->f &= (info->f & F_PLUS) ? ~F_SPACE : 524287;
	info->p = (info->f & PRECI) ? info->p : 6;
	if (!(res = get_type_f(info, (arg < 0) ? -arg : arg)))
		return ;
	len = ft_strlen(res);
	len += (info->f & CT_SIGN || info->f & F_PLUS || info->f & F_SPACE) ? 1 : 0;
	rest = (info->f & WIDTH && info->w > len) ? info->w - len : 0;
	info->len += (len + rest);
	print_f(info, res, rest);
	free(res);
}
