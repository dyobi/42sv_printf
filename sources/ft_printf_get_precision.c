/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_precision.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 02:48:15 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/18 02:48:17 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		set_precision(t_info *info, int prec)
{
	if ((!(info->p_info & P_DIRECT) && !(info->p_info & P_STAR)) || \
		(info->p_info & P_DIRECT && prec == 0))
		info->p_info |= P_ZERO;
	else
	{
		if (info->p != 0)
			info->p = info->p > prec ? prec : info->p;
		else
			info->p = prec;
	}
}

int			get_precision_star(t_info *info, va_list *ap)
{
	int		prec;

	prec = va_arg(*ap, int);

}

const char	*get_precision(t_info *info, va_list *ap, const char *s)
{
	int		prec;

	if (*s == 46)
	{
		s++;
		info->f |= PRECI;
		while (*s == 42 || (*s > 47 && *s < 58))
		{
			info->p = (*s == 42) ? get_precision_star(info, ap) : info->p;
			prec = 0;
			if (*s > 47 && *s < 58)
			{
				while (*s > 47 && *s < 58)
				{
					info->p_info |= P_DIRECT;
					prec = prec * 10 + *s - 48;
					s++;
				}
				s--;
			}
			set_precision(info, prec);
			s++;
		}
	}
	return (s);
}
