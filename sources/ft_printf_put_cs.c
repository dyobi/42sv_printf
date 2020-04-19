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

void	put_type_c(t_info *info)
{
	unsigned char	c;
	int				index;

	index = 1;
	c = (unsigned char)va_arg(info->ap, int);
	if (info->f & F_MINUS)
	{
		ft_putchar(c);
		while (i++ < info->w)
			ft_putchar(32);
	}
	else if (info->w)
	{
		while (i++ < info->w)
			(info->f & F_ZERO) ? ft_putchar(48) : ft_putchar(32);
		ft_putchar(c);
	}
	else
		ft_putchar(c);
	info->len += (info->w > 0) ? info->w : 1;
}
