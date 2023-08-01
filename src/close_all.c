/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/08/01 14:08:03 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_(int fildes)
{
	if (close (fildes) == -1)
		perror ("Problem with close() call");
}

void	close_pipes(void)
{
	t_data	*pipex;
	int		i;

	i = 0;
	pipex = get_data();
	while (i < 2 && pipex->pipes[i] > 0)
	{
		close_(pipex->pipes[i]);
		i++;
	}
}

void	close_files(void)
{
	t_data	*pipex;
	int		i;

	i = 0;
	pipex = get_data();
	while (i < 2 && pipex->files[i] > 0)
	{
		close_(pipex->files[i]);
		i++;
	}
}

void	close_all(void)
{
	close_files();
	close_pipes();
}
