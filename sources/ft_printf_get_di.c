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

void	put_type_di(t_info *info)
{
	int64_t	arg;
	char	*res;
	int		len;
	int		rest;

	arg = get_arg_type(info);
	info->f &= (info->f & PRECI) ? ~F_ZERO : 1;
	info->f &= (arg < 0) ? ~F_PLUS : 1;
	info->f |= (arg < 0) ? CT_SIGNED : 0;
	if (!(res = max_itoa_base((arg < 0 ? -(uint64_t)arg : arg), 10)))
		return ;
	len = (info->p > (rest = ft_strlen(res))) ? info->p : rest;
	len += (info->f & F_PLUS || info->f & CT_SIGNED) ? 1 : 0;
	rest = (info->f & WIDTH && info->w > len) ? info->w - len : 0;
	info->len += (len + rest);
}
