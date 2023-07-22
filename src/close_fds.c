/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/07/21 19:24:38 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_fds(int num_args, ...)
{
	va_list	ap;
	int	*fildes;
	int	i;
	int	j;

	i = 0;
	va_start (ap, num_args);
	while (i < num_args)
	{
		j = 0;
		fildes = va_arg (ap, int *);
		while (fildes[j])
		{
			close_(fildes[j]);
			j++;
		}
		i++;
	}
	va_end (ap);
}
