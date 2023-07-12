/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:37:25 by oroy              #+#    #+#             */
/*   Updated: 2023/07/04 17:41:04 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	write_arg(char c, void *arg, int fd)
{
	int	nbr;

	nbr = 0;
	if (c == 'c')
		nbr = ft_putchar_rtn_fd((char)arg, fd);
	else if (c == 's')
	{
		if (!arg)
			return (ft_putstr_rtn_fd("(null)", fd));
		nbr = ft_putstr_rtn_fd((char *)arg, fd);
	}
	else if (c == 'p')
	{
		nbr = ft_putstr_rtn_fd("0x", fd);
		if (nbr == -1)
			return (-1);
		nbr = ft_add(ft_puthex_rtn_fd((unsigned long)arg, c, fd), nbr);
	}
	else if (c == 'd' || c == 'i')
		nbr = ft_putnbr_rtn_fd((int)arg, fd);
	else if (c == 'u')
		nbr = ft_putnbr_rtn_fd((unsigned int)arg, fd);
	else if (c == 'x' || c == 'X')
		nbr = ft_puthex_rtn_fd((unsigned int)arg, c, fd);
	return (nbr);
}

int	ft_printf(const char *s, ...)
{
	va_list	valist;
	size_t	i;
	int		nbr;

	if (!s)
		return (0);
	i = 0;
	nbr = 0;
	va_start(valist, s);
	while (s[i] && nbr > -1)
	{
		if (s[i] == '%')
		{
			if (s[++i] == '%')
				nbr = ft_add(ft_putchar_rtn_fd('%', 1), nbr);
			else
				nbr = ft_add(write_arg(s[i], va_arg(valist, void *), 1), nbr);
		}
		else
			nbr = ft_add(ft_putchar_rtn_fd(s[i], 1), nbr);
		i++;
	}
	va_end(valist);
	return (nbr);
}
