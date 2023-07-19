/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:15:55 by oroy              #+#    #+#             */
/*   Updated: 2023/07/19 13:46:17 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	*ft_null(void *rtn)
{
	if (!rtn)
	{
		ft_putstr_fd("Error: NULL returned", 2);
		exit (EXIT_FAILURE);
	}
	else
		return (rtn);
}