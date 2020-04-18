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

int		ft_main(t_info *info, va_list *ap, const char *s)
{
	while (*s)
	{
		if (*s == '%')
		{
			s = get_info(info, ap, ++s);
			if (!get_valid(info, ap, s))
				break ;
			info->len += get_conversion(info, ap, s);
		}
		else
		{
			ft_putchar(*s);
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
	va_start(ap, s);
	res = ft_main(&info, &ap, s);
	va_end(ap);
	return (res);
}
