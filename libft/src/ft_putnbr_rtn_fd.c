/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_rtn_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:51:59 by oroy              #+#    #+#             */
/*   Updated: 2023/06/30 22:13:23 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putnbr_rtn_fd(long n, int fd)
{
	int	nbr;

	nbr = 0;
	if (n < 0)
	{
		nbr = ft_putchar_rtn_fd('-', fd);
		if (nbr == -1)
			return (-1);
		n = -n;
	}
	if (n / 10 != 0)
	{
		nbr = ft_add(ft_putnbr_rtn_fd(n / 10, fd), nbr);
		if (nbr == -1)
			return (-1);
	}
	return (ft_add(ft_putchar_rtn_fd(n % 10 + 48, fd), nbr));
}
