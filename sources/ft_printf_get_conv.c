/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_conv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:50:07 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/18 16:50:08 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_dt	g_dt[] =
{
	{37, put_type_c},
	{99, put_type_c},
	{115, put_type_s},
	{100, put_type_di},
	{105, put_type_di},
	{0, NULL}
};

int64_t	get_arg_type(t_info *info)
{
	int64_t	res;

	if (info->f & CT_U && info->f & LT_LL)
		return (va_arg(info->ap, unsigned long long));
	else if ((info->f & LT_L || info->f & LT_LL) && (info->f & CT_HEXUP || \
		info->f & CT_HEXDN))
		return (va_arg(info->ap, unsigned long));
	else if (info->f & LT_BIGL)
		return (va_arg(info->ap, long double));
	else if (info->f & LT_LL)
		return (va_arg(info->ap, long long));
	else if (info->f & LT_L)
		return (va_arg(info->ap, long));
	else if (info->f & LT_Z)
		return (va_arg(info->ap, size_t));
	res = va_arg(info->ap, int);
	res = (info->f & LT_H) ? (short)res : res;
	res = (info->f & LT_HH) ? (char)res : res;
	return (res);
}

void	get_conversion(t_info *info, const char *s)
{
	int		index;

	index = 0;
	while (*s && index < 5)
	{
		if (*s == g_dt[index].specifier)
		{
			g_dt[index].ft(info);
			break ;
		}
		index++;
	}
}
