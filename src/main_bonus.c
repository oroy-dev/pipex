/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/24 17:44:58 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*path_to_exec(char **pathlist, char *cmd, int fds[2][2])
{
	char	*path;
	int		i;

	i = 0;
	while (pathlist[i])
	{
		path = ft_strjoin(pathlist[i], cmd);
		malloc_check(path, fds);
		if (access (path, X_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	return (NULL);
}

static void	exec_cmd(int fildes[2], char *path, char **cmd, int fds[2][2])
{
	dup2_(fildes[1], STDOUT_FILENO, fds);
	close_(fildes[1]);
	close_(fildes[0]);
	execve_(path, cmd, NULL, fds);
}

static void	child_process(int count, char *path, char **cmd, int fds[2][2])
{
	dup2_(fds[0][0], STDIN_FILENO, fds);
	if (count > 1)
	{
		close_(fds[0][1]);
		close_(fds[0][0]);
		exec_cmd(fds[1], path, cmd, fds);
	}
	else
		exec_cmd(fds[0], path, cmd, fds);
	exit (EXIT_FAILURE);
}

static void	pipex(int fds[2][2], char **argv, char **pathlist, int count)
{
	char	**cmd;
	char	*path;
	pid_t	process;
	int		status;
	int		i;

	i = 0;
	while (i < count)
	{
		if (i < count - 1)
			pipe_(fds);
		// get_exec_info(argv[i + 2], path, cmd, fds);
		cmd = ft_split(argv[i + 2], ' ');
		malloc_check(cmd, fds);
		path = ft_strjoin("/", cmd[0]);
		malloc_check(path, fds);
		path = path_to_exec(pathlist, path, fds);
		if (!path)
		{
			ft_putendl_fd("Error: Shell Command Not Executable", 2);
			close_all_fds(fds);
			exit (EXIT_FAILURE);
		}
		process = fork_(fds);
		child_process(count - i, path, cmd, fds);
		waitpid_(process, &status, 0);
		if (i < count - 1)
		{
			dup2_(fds[1][0], fds[0][0], fds);
			close_(fds[1][0]);
			close_(fds[1][1]);
		}
		ft_free_tab((void **)cmd);
		ft_free(path);
		i++;
	}
	close_all_fds(fds);
}

static char	**getpathlist(char **envp, char *path, int fds[2][2])
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
			malloc_check(pathstr, fds);
			pathlist = ft_split(pathstr, ':');
			ft_free (pathstr);
			malloc_check(pathlist, fds);
			return (pathlist);
		}
		i++;
	}
	return (NULL);
}

static void	open_files(int argc, char **argv, int files[2])
{
	files[0] = open (argv[1], O_RDONLY);
	if (files[0] == -1)
	{
		perror ("Can't open infile");
		exit (EXIT_FAILURE);
	}
	files[1] = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files[1] == -1)
	{
		perror ("Can't open/create outfile");
		close_(files[0]);
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2][2];
	char	**pathlist;

	if (argc < 5)
	{
		ft_putendl_fd("Error: Lower number of arguments than required", 2);
		exit (EXIT_FAILURE);
	}
	open_files(argc, argv, fds[0]);
	pathlist = getpathlist(envp, "PATH=", fds);
	if (!pathlist)
	{
		ft_putendl_fd("Error: Can't find path list", 2);
		close_all_fds(fds);
		exit (EXIT_FAILURE);
	}
	pipex(fds, argv, pathlist, argc - 3);
	ft_free_tab((void **)pathlist);
	return (0);
}
