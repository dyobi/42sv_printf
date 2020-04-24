/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_di.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 20:12:26 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/21 20:12:27 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		max_itoa_base_len(uint64_t n, uint64_t base)
{
	int		len;

	len = 0;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}

char	*max_itoa_base(uint64_t n, uint64_t base)
{
	int64_t	tmp;
	char	*res;
	int		len;

	len = max_itoa_base_len(n, base);
	if (!(res = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		tmp = n % base;
		n /= base;
		res[len] = (tmp > 9) ? (tmp - 10 + 'a') : (tmp + '0');
	}
	return (res);
}

void	print_diu(t_info *info, char *res, int len, int rest)
{
	(info->f & F_SPACE) ? put_tok(32, 1) : 0;
	(!(info->f & F_MINUS) && !(info->f & F_ZERO)) ? put_tok(32, rest) : 0;
	(info->f & CT_SIGN) ? put_tok(45, 1) : 0;
	(info->f & F_PLUS) ? put_tok(43, 1) : 0;
	len -= (info->f & F_PLUS || info->f & CT_SIGN) ? 1 : 0;
	len -= (info->f & F_SPACE) ? 1 : 0;
	(info->p > ft_strlen(res)) ? put_tok(48, len - ft_strlen(res)) : 0;
	while (*res)
		ft_putchar_fd(*(res++), 1);
	(info->f & F_MINUS) ? put_tok(32, rest) : 0;
}

void	put_type_di(t_info *info)
{
	int64_t	arg;
	char	*res;
	int		len;
	int		rest;

	arg = get_arg_type(info);
	info->f &= (info->f & PRECI) ? ~F_ZERO : 262143;
	info->f &= (arg < 0) ? ~F_PLUS : 262143;
	info->f |= (arg < 0) ? CT_SIGN : 0;
	info->f &= (info->f & F_PLUS || info->f & CT_SIGN) ? ~F_SPACE : 262143;
	if (!(res = max_itoa_base((arg < 0 ? -(uint64_t)arg : arg), 10)))
		return ;
	len = (info->p > ft_strlen(res)) ? info->p : ft_strlen(res);
	len += (info->f & F_PLUS || info->f & CT_SIGN) ? 1 : 0;
	len += (info->f & F_SPACE) ? 1 : 0;
	rest = (info->f & WIDTH && info->w > len) ? info->w - len : 0;
	info->len += (len + rest);
	print_diu(info, res, len, rest);
	free(res);
}

void	put_type_u(t_info *info)
{
	int64_t	arg;
	char	*res;
	int		len;
	int		rest;

	arg = get_arg_type(info);
	arg = !(info->f & LT_L) && info->f & LT_H ? (unsigned short)arg : arg;
	arg = !(info->f & LT_L) && info->f & LT_HH ? (unsigned char)arg : arg;
	info->f &= (~F_PLUS & ~F_SPACE);
	info->f &= (info->f & PRECI) ? ~F_ZERO : 262143;
	if (!(res = max_itoa_base((info->f & LT_L || info->f & LT_LL) ? \
		(uint64_t)arg : (unsigned)arg, 10)))
		return ;
	len = (info->p > ft_strlen(res)) ? info->p : ft_strlen(res);
	rest = (info->f & WIDTH && info->w > len) ? info->w - len : 0;
	info->len += (len + rest);
	print_diu(info, res, len, rest);
	free(res);
}
