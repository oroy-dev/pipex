/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/07/20 21:04:37 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipe_(int fildes[2])
{
	if (pipe (fildes) == -1)
	{
		perror("Problem with pipe() call");
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
		exit (EXIT_FAILURE);
	}
	return (process);
}

void	dup2_(int fildes, int fildes2)
{
	if (dup2 (fildes, fildes2) == -1)
	{
		perror ("Problem with dup2() call");
		exit (EXIT_FAILURE);
	}
}

void	close_(int fildes)
{
	if (close (fildes) == -1)
	{
		perror ("Problem with close() call");
		exit (EXIT_FAILURE);
	}
}

void	execve_(const char *path, char *const argv[], char *const envp[])
{
	if (execve (path, argv, envp) == -1)
	{
		perror ("Problem with execve() call");
		exit (EXIT_FAILURE);
	}
}

void	waitpid_(pid_t pid, int *status, int options)
{
	if (waitpid (pid, status, options) == -1)
	{
		perror ("Problem with waitpid() call");
		exit (EXIT_FAILURE);
	}
	else if (WIFEXITED (*status) && WEXITSTATUS (*status) != 0)
	{
		ft_putstr_fd("Child process did not exit correctly\n", 2);
		exit (EXIT_FAILURE);
	}
}
