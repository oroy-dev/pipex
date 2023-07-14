/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/14 19:36:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*path_to_exec(char **pathlist, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (pathlist[i])
	{
		path = ft_strjoin(pathlist[i], "/");
		path = ft_strjoin(path, cmd);
		if (access (path, X_OK) == 0)
			break ;
		free (path);
		i++;
	}
	return (path);
}

void	pipex(int in, int out, char **argv, char **pathlist, int argc)
{
	int		fd_pipe[2];
	char	**cmd;
	char	*path;
	pid_t	pid1;
	int		i;

	i = 2;
	while (i < argc - 2)
	{
		if (pipe (fd_pipe) == -1)
			exit (EXIT_FAILURE);
		pid1 = fork ();
		if (pid1 == -1)
			exit (EXIT_FAILURE);
		else if (!pid1)
		{
			dup2 (in, STDIN_FILENO);
			dup2 (fd_pipe[1], STDOUT_FILENO);
			close (fd_pipe[0]);
			cmd = ft_split(argv[i], ' ');
			path = path_to_exec(pathlist, cmd[0]);
			execve (path, cmd, NULL);
			free (path);
			close (fd_pipe[1]);
			exit (EXIT_SUCCESS);
		}
		waitpid (pid1, NULL, 0);
		// dup2 (fd_pipe[0], STDIN_FILENO);
		dup2 (in, fd_pipe[0]);
		close (fd_pipe[1]);
		close (fd_pipe[0]);
		i++;
	}
	dup2 (out, STDOUT_FILENO);
	cmd = ft_split(argv[i], ' ');
	path = path_to_exec(pathlist, cmd[0]);
	execve (path, cmd, NULL);
	// close (fd_pipe[0]);
	close (in);
	close (out);
	free (path);
	path = NULL;
}

static char	**getpathlist(char **envp, char *path)
{
	char	**pathlist;
	char	*pathstr;
	size_t	len;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], path, 5))
		{
			len = ft_strlen(envp[i]);
			pathstr = ft_substr(envp[i], 5, len);
			pathlist = ft_split(pathstr, ':');
			free (pathstr);
			pathstr = NULL;
			return (pathlist);
		}
		i++;
	}
	ft_putstr_rtn_fd("Error: Can't find path list\n", 2);
	exit (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	**pathlist;
	int		out;
	int		in;

	if (argc >= 5)
	{
		in = open (argv[1], O_RDONLY);
		out = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (in == -1 || out == -1)
		{
			ft_putstr_rtn_fd("Error: Can't open input and/or output files\n", 2);
			return (1);
		}
		pathlist = getpathlist(envp, "PATH=");
		pipex(in, out, argv, pathlist, argc);
		// Might need to free in pipex() call
		free (pathlist);
		pathlist = NULL;
	}
	else
	{
		ft_putstr_rtn_fd("Error: Lower number of arguments than required\n", 2);
		return (1);
	}
	return (0);
}
