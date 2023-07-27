/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/07/27 12:04:05 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_(int fildes)
{
	if (close (fildes) == -1)
	{
		perror ("Problem with close() call");
		exit (EXIT_FAILURE);
	}
}

void	close_all(void)
{
	t_data	*pipex;
	int		i;
	int		j;

	i = 0;
	j = 0;
	pipex = get_data();
	while (pipex->files && pipex->files[i] > 0)
	{
		close_(pipex->files[i]);
		i++;
	}
	while (pipex->pipes && pipex->pipes[j] > 0)
	{
		close_(pipex->pipes[j]);
		j++;
	}
}
