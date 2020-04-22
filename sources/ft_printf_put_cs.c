/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_cs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 18:56:00 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/18 18:56:01 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	put_tok(char c, int len)
{
	while (len-- > 0)
		ft_putchar_fd(c, 1);
}

void	put_type_s(t_info *info)
{
	char	*arg;
	int		len;
	int		rest;

	arg = va_arg(info->ap, char*);
	arg = (arg == NULL) ? "(null)" : arg;
	len = (info->f & PRECI) ? info->p : ft_strlen(arg);
	rest = (info->f & WIDTH && info->w > len) ? info->w - len : 0;
	info->len += (len + rest);
	(!(info->f & F_MINUS) && info->f & F_ZERO) ? put_tok(48, rest) : 0;
	(!(info->f & F_MINUS) && !(info->f & F_ZERO)) ? put_tok(32, rest) : 0;
	while (len-- > 0)
		ft_putchar_fd(*(arg++), 1);
	(info->f & F_MINUS) ? put_tok(32, rest) : 0;
}

void	put_type_c(t_info *info)
{
	unsigned char	c;

	c = (info->f & CT_PERCENT) ? 37 : (unsigned char)va_arg(info->ap, int);
	!(info->f & F_MINUS) && info->f & F_ZERO ? put_tok(48, info->w - 1) : 0;
	!(info->f & F_MINUS) && !(info->f & F_ZERO) ? put_tok(32, info->w - 1) : 0;
	ft_putchar_fd(c, 1);
	(info->f & F_MINUS) ? put_tok(32, info->w - 1) : 0;
	info->len += (info->w > 0) ? info->w : 1;
}
