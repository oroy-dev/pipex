/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/17 17:13:14 by oroy             ###   ########.fr       */
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
	int		pipes[argc - 4][2];
	pid_t	pids[argc - 4];
	char	**cmd;
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < argc - 4)
	{
		if (pipe (pipes[j]) == -1)
			exit (EXIT_FAILURE);
		j++;
	}
	while (i < argc - 4)
	{
		pids[i] = fork ();
		if (pids[i] == -1)
			exit (EXIT_FAILURE);
		else if (!pids[i])
		{
			if (!i)
				dup2 (in, STDIN_FILENO);
			else
				dup2 (pipes[i - 1][0], STDIN_FILENO);
			dup2 (pipes[i][1], STDOUT_FILENO);
			close (pipes[i][0]);
			cmd = ft_split(argv[i + 2], ' ');
			path = path_to_exec(pathlist, cmd[0]);
			execve (path, cmd, NULL);
			free (path);
			close (pipes[i][1]);
			exit (EXIT_SUCCESS);
		}
		waitpid (pids[i], NULL, 0);
		close (pipes[i][1]);
		i++;
	}
	dup2 (pipes[i - 1][0], STDIN_FILENO);
	dup2 (out, STDOUT_FILENO);
	close (in);
	cmd = ft_split(argv[i + 2], ' ');
	path = path_to_exec(pathlist, cmd[0]);
	execve (path, cmd, NULL);
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
