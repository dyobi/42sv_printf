/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 23:11:18 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/17 23:11:21 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

const char	*get_flags(t_info *info, const char *s)
{
	while (*s == 32 || *s == 35 || *s == 43 || *s == 45 || *s == 48)
	{
		info->f |= (*s == 32) ? F_SPACE : 0;
		info->f |= (*s == 43) ? F_PLUS : 0;
		info->f |= (*s == 45) ? F_MINUS : 0;
		info->f |= (*s == 48) ? F_ZERO : 0;
		info->f |= (*s == 35) ? F_HASH : 0;
		s++;
	}
	return (s);
}

const char	*get_modifier(t_info *info, const char *s)
{
	while (*s == 76 || *s == 104 || *s == 108 || *s == 122)
	{
		if (*s == 104 && *(s + 1) == 104 && *(s++) && *(s++))
			info->f |= LT_HH;
		else if (*s == 104 && *(s++))
			info->f |= LT_H;
		else if (*s == 108 && *(s + 1) == 108 && *(s++) && *(s++))
			info->f |= LT_LL;
		else if (*s == 108 && *(s++))
			info->f |= LT_L;
		else if (*s == 122 && *(s++))
			info->f |= LT_Z;
		else if (*s == 76 && *(s++))
			info->f |= LT_BIGL;
	}
	return (s);
}

const char	*get_width(t_info *info, const char *s)
{
	while (*s == 42 || *s == 45 || (*s > 47 && *s < 58))
	{
		info->f |= WIDTH;
		info->w = (*s == 42) ? va_arg(info->ap, int) : info->w;
		if (*s > 47 && *s < 58)
		{
			info->w = 0;
			while (*s > 47 && *s < 58)
			{
				info->w = info->w * 10 + *s - 48;
				s++;
			}
		}
		else
		{
			info->f |= (*s == 45 || info->w < 0) ? F_MINUS : 0;
			info->w = (info->w < 0) ? -info->w : info->w;
			s++;
		}
	}
	return (s);
}

const char	*get_precision(t_info *info, const char *s)
{
	int		sign;

	sign = 0;
	info->p = 0;
	info->f |= PRECI;
	if (*s == 45 || (*s > 47 && *s < 58))
	{
		sign = (*s == 45 && *(s++)) ? 1 : 0;
		while (*s > 47 && *s < 58)
		{
			info->p = info->p * 10 + *s - 48;
			s++;
		}
	}
	else if (*s == 42 && *(s++))
		info->p = va_arg(info->ap, int);
	info->p = (info->p < 0 || sign) ? 0 : info->p;
	return (s);
}

const char	*get_info(t_info *info, const char *s)
{
	while (*s == 32 || *s == 35 || *s == 42 || *s == 43 || *s == 45 || \
		*s == 46 || (*s > 47 && *s < 58) || *s == 76 || *s == 104 || \
		*s == 108 || *s == 122)
	{
		s = get_flags(info, s);
		s = get_modifier(info, s);
		s = get_width(info, s);
		s = (*s == 46) ? get_precision(info, s + 1) : s;
	}
	return (s);
}
