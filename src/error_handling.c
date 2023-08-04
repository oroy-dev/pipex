/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/08/04 14:10:41 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipe_(int fildes[2])
{
	if (pipe (fildes) == -1)
	{
		perror("Problem with pipe() call");
		close_all();
		free_data();
		exit (EXIT_FAILURE);
	}
}

pid_t	fork_(void)
{
	pid_t	process;

	process = fork ();
	if (process == -1)
	{
		perror ("Problem with fork() call");
		close_all();
		free_data();
		exit (EXIT_FAILURE);
	}
	return (process);
}

void	execve_(char *path, char **cmd, char **envp)
{
	if (execve (path, cmd, envp) == -1)
	{
		perror ("Problem with execve() call");
		free_data();
		exit (EXIT_FAILURE);
	}
}

void	waitpid_(pid_t pid, int *status, int options)
{
	if (waitpid (pid, status, options) == -1)
	{
		perror ("Problem with waitpid() call");
		close_all();
		free_data();
		exit (EXIT_FAILURE);
	}
}
