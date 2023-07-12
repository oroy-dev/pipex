/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:13:16 by oroy              #+#    #+#             */
/*   Updated: 2023/07/12 12:35:34 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_atoi(const char *str)
{
	char	*p;
	int		n;
	int		minus;

	if (!str)
		return (0);
	n = 0;
	minus = 1;
	p = (char *)str;
	while (*p == 32 || (*p > 8 && *p < 14))
		p++;
	if (*p == '+' || *p == '-')
	{
		if (*p == '-')
			minus *= -1;
		p++;
	}
	while (*p >= '0' && *p <= '9')
	{
		n *= 10;
		n += *p - 48;
		p++;
	}
	return (n * minus);
}
