/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilkim <kilkim@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 21:32:09 by kilkim            #+#    #+#             */
/*   Updated: 2020/04/21 21:32:11 by kilkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		max_itoa_base_len(uint64_t n, uint64_t base)
{
	int		len;

	len = 0;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}

char	*max_itoa_base(uint64_t n, uint64_t base)
{
	int64_t	tmp;
	char	*res;
	int		len;

	len = max_itoa_base_len(n, base);
	if (!(res = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		tmp = n % base;
		n /= base;
		res[len] = (tmp > 9) ? (tmp - 10 + 'a') : (tmp + '0');
	}
	return (res);
}
