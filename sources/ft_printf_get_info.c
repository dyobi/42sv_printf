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

void		init_info(t_info *info)
{
	info->f = 0;
	info->w = 0;
	info->p = 0;
	info->p_info = 0;
}

const char	*get_flags(t_info *info, const char *s)
{
	while (*s == 32 || *s == 35 || *s == 43 || *s == 45 || *s == 48)
	{
		info->f = (*s == 32) ? info->f | F_SPACE : info->f;
		info->f = (*s == 43) ? info->f | F_PLUS : info->f;
		info->f = (*s == 45) ? info->f | F_MINUS : info->f;
		info->f = (*s == 48) ? info->f | F_ZERO : info->f;
		info->f = (*s == 35) ? info->f | F_HASH : info->f;
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

const char	*get_info(t_info *info, va_list *ap, const char *s)
{
	init_info(info);
	while (*s == 32 || *s == 35 || *s == 42 || *s == 43 || *s == 45 || \
		*s == 46 || (*s > 47 && *s < 58) || *s == 76 || *s == 104 || \
		*s == 108 || *s == 122)
	{
		s = get_flags(info, s);
		s = get_modifier(info, s);
		s = get_width(info, ap, s);
		s = get_precision(info, ap, s);
	}
	return (s);
}
