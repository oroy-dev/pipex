/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:49:02 by oroy              #+#    #+#             */
/*   Updated: 2023/07/27 10:56:42 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	malloc_check(void *maloc)
{
	if (!maloc)
	{
		ft_putendl_fd("Malloc Error", 2);
		close_all();
		free_data();
		exit (EXIT_FAILURE);
	}
}
