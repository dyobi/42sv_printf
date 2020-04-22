/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:42:16 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/17 21:42:16 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		get_valid(t_info *info, const char *s)
{
	info->f |= (*s == 37) ? CT_PERCENT : 0;
	info->f |= (*s == 117) ? CT_U : 0;
	info->f |= (*s == 88) ? CT_HEXUP : 0;
	info->f |= (*s == 120) ? CT_HEXDN : 0;
	return ((*s == 37 || *s == 88 || *s == 99 || *s == 100 || *s == 102 || \
		*s == 105 || *s == 112 || *s == 115 || *s == 117 || *s == 120) ? 1 : 0);
}

int		ft_main(t_info *info, const char *s)
{
	while (*s)
	{
		if (*s == 37)
		{
			s = get_info(info, ++s);
			if (!get_valid(info, s))
				break ;
			get_conversion(info, s);
		}
		else
		{
			ft_putchar_fd(*s, 1);
			info->len++;
		}
		s++;
	}
	return (info->len);
}

int		ft_printf(const char *s, ...)
{
	va_list	ap;
	t_info	info;
	int		res;

	ft_bzero(&info, sizeof(info));
	va_start(info.ap, s);
	res = ft_main(&info, s);
	va_end(info.ap);
	return (res);
}
