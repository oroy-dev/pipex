/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/19 13:45:28 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*path_to_exec(char **pathlist, char *cmd)
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

static void	exec_cmd(int in, int out, char *arg, char **pathlist)
{
	char	**cmd;
	char	*path;

	dup2 (out, STDOUT_FILENO);
	close (in);
	cmd = ft_split(arg, ' ');
	path = path_to_exec(pathlist, cmd[0]);
	execve (path, cmd, NULL);
	free (path);
	path = NULL;
	close (out);
}

static void	pipex(int files[2], char **argv, char **pathlist, int count)
{
	int		pipes[2];
	pid_t	process;
	int		i;

	i = 0;
	while (i < count)
	{
		if (pipe (pipes) == -1)
			exit (EXIT_FAILURE);
		process = fork ();
		if (process == -1)
			exit (EXIT_FAILURE);
		else if (!process)
		{
			dup2 (files[0], STDIN_FILENO);
			exec_cmd(pipes[0], pipes[1], argv[i + 2], pathlist);
			exit (EXIT_SUCCESS);
		}
		waitpid (process, NULL, 0);
		dup2 (pipes[0], files[0]);
		close (pipes[1]);
		i++;
	}
	dup2 (pipes[0], STDIN_FILENO);
	exec_cmd(files[0], files[1], argv[i + 2], pathlist);
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
			pathstr = (char *)ft_null(ft_substr(envp[i], 5, len));
			pathlist = (char **)ft_null(ft_split(pathstr, ':'));
			free (pathstr);
			pathstr = NULL;
			return (pathlist);
		}
		i++;
	}
	ft_putstr_fd("Error: Can't find path list\n", 2);
	exit (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	**pathlist;
	int		files[2];

	if (argc >= 5)
	{
		files[0] = open (argv[1], O_RDONLY);
		files[1] = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (files[0] == -1 || files[1] == -1)
		{
			ft_putstr_fd("Error: Can't open input and/or output files\n", 2);
			return (1);
		}
		pathlist = getpathlist(envp, "PATH=");
		pipex(files, argv, pathlist, argc - 4);
		// Might need to free in pipex() call
		free (pathlist);
		pathlist = NULL;
	}
	else
	{
		ft_putstr_fd("Error: Lower number of arguments than required\n", 2);
		return (1);
	}
	return (0);
}
