/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:42:00 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/17 21:42:01 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// FLAGS

# define F_SPACE 1
# define F_PLUS 2
# define F_MINUS 4
# define F_ZERO 8
# define F_HASH 16

// WIDTH & PRECISION

# define WIDTH 32
# define PRECI 64

// LENGTH_TYPE

# define LT_L 128
# define LT_LL 256
# define LT_H 512
# define LT_HH 1024

// CONVERSION_TYPE

# define CT_HEXUP 2048
# define CT_HEXDN 4096

typedef struct	s_dispatch_table
{
	char	specifier;
	int		(*ft)();
}				t_dt;

typedef struct	s_info
{
	va_list	ap;
	int		f;
	int		w;
	int		w_s;
	int		p;
	int		p_s;
	int		len;
}				t_info;

#endif
