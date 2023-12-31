/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/08/03 17:05:26 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_(int fildes)
{
	if (close (fildes) == -1)
		perror ("Problem with close() call");
}

void	close_tab(int fildes[2])
{
	int	i;

	i = 0;
	while (i < 2 && fildes[i] > 0)
	{
		close_(fildes[i]);
		fildes[i] = 0;
		i++;
	}
}

void	close_all(void)
{
	t_data	*pipex;

	pipex = get_data();
	close_tab(pipex->files);
	close_tab(pipex->pipes);
}
