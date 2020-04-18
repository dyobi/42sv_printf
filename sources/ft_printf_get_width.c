/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_width.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 01:57:19 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/18 01:57:20 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			get_width_star(t_info *info, va_list *ap)
{
	int		width;

	width = va_arg(*ap, int);
	if (!(info->f & WIDTH))
	{
		info->f = (width < 0) ? info->f | F_MINUS : info->f;
		width = (width < 0) ? -width : width;
		return (width);
	}
	else
		return (info->w);
}

const char	*get_width(t_info *info, va_list *ap, const char *s)
{
	int		width;

	while (*s == 42 || *s == 45 || (*s > 47 && *s < 58))
	{
		info->w = (*s == 42) ? get_width_star() : info->w;
		info->f = (*s == 45) ? info->f | F_MINUS : info->f;
		if (*s > 47 && *s < 58)
		{
			width = 0;
			info->w = (info->f & WIDTH) ? info->w : 0;
			while (*s > 47 && *s < 58)
			{
				info->f |= WIDTH;
				width = width * 10 + *s - 48;
				s++;
			}
			info->w = width > info->w ? width : info->w;
		}
		else
			s++;
	}
	return (s);
}
