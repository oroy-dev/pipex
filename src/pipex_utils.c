/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/07/19 14:09:25 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipe_(int pipes[2])
{
	if (pipe (pipes) == -1)
	{
		ft_putstr_fd("Error: Pipe Creation Unsuccessful", 2);
		exit (EXIT_FAILURE);
	}
}

pid_t	fork_(void)
{
	pid_t	process;

	process = fork ();
	if (process == -1)
	{
		ft_putstr_fd("Error: Forking Unsuccessful", 2);
		exit (EXIT_FAILURE);
	}
	return (process);
}

void	dup2_(int fildes, int fildes2)
{
	if (dup2 (fildes, fildes2) == -1)
	{
		ft_putstr_fd("Error: FD Duplication Unsuccessful", 2);
		exit (EXIT_FAILURE);
	}
}

void	close_(int fildes)
{
	if (close (fildes) == -1)
	{
		ft_putstr_fd("Error: FD Closing Unsuccessful", 2);
		exit (EXIT_FAILURE);
	}
}


