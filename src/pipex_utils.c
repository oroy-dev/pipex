/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/07/24 14:08:50 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipe_(int fds[2][2])
{
	if (pipe (fds[1]) == -1)
	{
		perror("Problem with pipe() call");
		close_all_fds(fds);
		exit (EXIT_FAILURE);
	}
}

pid_t	fork_(int fds[2][2])
{
	pid_t	process;

	process = fork ();
	if (process == -1)
	{
		perror ("Problem with fork() call");
		close_all_fds(fds);
		exit (EXIT_FAILURE);
	}
	return (process);
}

void	dup2_(int fildes, int fildes2, int fds[2][2])
{
	if (dup2 (fildes, fildes2) == -1)
	{
		perror ("Problem with dup2() call");
		close_all_fds(fds);
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

void	execve_(char *path, char **cmd, char **envp, int fds[2][2])
{
	if (execve (path, cmd, envp) == -1)
	{
		perror ("Problem with execve() call");
		close_all_fds(fds);
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
		ft_putendl_fd("Child process did not exit correctly", 2);
		exit (EXIT_FAILURE);
	}
}
