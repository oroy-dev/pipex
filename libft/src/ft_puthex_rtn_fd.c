/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_rtn_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:14:57 by oroy              #+#    #+#             */
/*   Updated: 2023/07/04 13:15:17 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	convert_char(unsigned int n, char c)
{
	if (n < 10)
		return (n + 48);
	else
	{
		if (c == 'X')
			return (n + 55);
		else
			return (n + 87);
	}
}

int	ft_puthex_rtn_fd(unsigned long n, char c, int fd)
{
	int	nbr;

	nbr = 0;
	if (n / 16 != 0)
	{
		nbr = ft_puthex_rtn_fd(n / 16, c, fd);
		if (nbr == -1)
			return (-1);
	}
	return (ft_add(ft_putchar_rtn_fd(convert_char(n % 16, c), fd), nbr));
}
