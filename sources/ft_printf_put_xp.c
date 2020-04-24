/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_xp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 23:23:47 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/23 23:23:52 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_xp(t_info *info, char *res, int len, int rest)
{
	(!(info->f & F_MINUS) && !(info->f & F_ZERO)) ? put_tok(32, rest) : 0;
	(!(info->f & F_MINUS) && info->f & F_ZERO) ? put_tok(48, rest) : 0;
	(info->f & F_HASH && info->f & CT_HEXUP) ? write(1, "0X", 2) : 0;
	(info->f & F_HASH && !(info->f & CT_HEXUP)) ? write(1, "0x", 2) : 0;
	len -= (info->f & F_HASH) ? 2 : 0;
	len -= (info->f & CT_P) ? 2 : 0;
	(info->p > ft_strlen(res)) ? put_tok(48, len - ft_strlen(res)) : 0;
	(info->f & CT_P) ? write(1, "10", 2) : 0;
	while (*res)
		ft_putchar_fd((info->f & CT_HEXUP && !(*res > 47 && *res < 58)) ? \
		*(res++) - 32 : *(res++), 1);
	(info->f & F_MINUS) ? put_tok(32, rest) : 0;
}

void	put_type_xp(t_info *info)
{
	int64_t	arg;
	char	*res;
	int		len;
	int		rest;

	arg = (info->f & CT_HEXUP || info->f & CT_HEXDN) ? \
		get_arg_type(info) : (int64_t)va_arg(info->ap, void*);
	arg = (!(info->f & CT_P) && info->f & LT_H) ? (unsigned short)arg : arg;
	arg = (!(info->f & CT_P) && info->f & LT_HH) ? (unsigned char)arg : arg;
	info->f |= (info->f & CT_P) ? F_HASH : 0;
	info->f &= (info->f & PRECI) ? ~F_ZERO : 524287;
	if (!(res = max_itoa_base((info->f & LT_L || info->f & LT_LL) ? \
		(uint64_t)arg : (unsigned)arg, 16)))
		return ;
	len = (info->p > ft_strlen(res)) ? info->p : ft_strlen(res);
	len += (info->f & F_HASH) ? 2 : 0;
	len += (info->f & CT_P && info->p < ft_strlen(res)) ? 2 : 0;
	rest = (info->f & WIDTH && info->f > len) ? info->w - len : 0;
	info->len += (len + rest);
	print_xp(info, res, len, rest);
	free(res);
}
