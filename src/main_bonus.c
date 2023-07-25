/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/25 14:06:14 by oroy             ###   ########.fr       */
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
		path = ft_strjoin(pathlist[i], cmd);
		malloc_check(path);
		if (access (path, X_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	return (NULL);
}

static void	child_process(int count, char *path, char **cmd)
{
	t_fds	*fds;

	fds = get_fds();
	dup2_(fds->files[0], STDIN_FILENO);
	if (count > 1)
	{
		dup2_(fds->pipes[1], STDOUT_FILENO);
		close_all();
		execve_(path, cmd, NULL);
	}
	else
	{
		dup2_(fds->files[1], STDOUT_FILENO);
		close_(fds->files[0]);
		close_(fds->files[1]);
		execve_(path, cmd, NULL);
	}
	exit (EXIT_FAILURE);
}

static char	**get_exec_info(char *arg, char **pathlist, char **path)
{
	char	**cmd;
	
	cmd = ft_split(arg, ' ');
	malloc_check(cmd);
	*path = ft_strjoin("/", cmd[0]);
	malloc_check(*path);
	*path = path_to_exec(pathlist, *path);
	if (!*path)
	{
		ft_putendl_fd("Error: Shell Command Not Executable", 2);
		close_all();
		exit (EXIT_FAILURE);
	}
	printf ("%s\n", *path);
	return (cmd);
}

static void	pipex(int count, char **argv, char **pathlist)
{
	char	**cmd;
	char	*path;
	t_fds	*fds;
	pid_t	process;
	int		status;
	int		i;

	i = 0;
	fds = get_fds();
	while (i < count)
	{
		cmd = get_exec_info(argv[i + 2], pathlist, &path);
		if (i < count - 1)
			pipe_();
		process = fork_();
		if (process == 0)
			child_process(count - i, path, cmd);
		waitpid_(process, &status, 0);
		if (i < count - 1)
		{
			dup2_(fds->pipes[0], fds->files[0]);
			close_all(fds->pipes);
		}
		ft_free_tab((void **)cmd);
		ft_free(path);
		i++;
	}
	close_all(fds->files);
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
			// malloc_check(pathstr);
			pathlist = ft_split(pathstr, ':');
			ft_free (pathstr);
			// malloc_check(pathlist);
			return (pathlist);
		}
		i++;
	}
	return (NULL);
}

static void	open_files(int argc, char **argv)
{
	t_fds	*fds;

	fds = get_fds();
	fds->files[0] = open (argv[1], O_RDONLY);
	if (fds->files[0] == -1)
	{
		perror ("Can't open infile");
		exit (EXIT_FAILURE);
	}
	fds->files[1] = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->files[1] == -1)
	{
		perror ("Can't open/create outfile");
		close_(fds->files[0]);
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**pathlist;

	if (argc < 5)
	{
		ft_putendl_fd("Error: Lower number of arguments than required", 2);
		exit (EXIT_FAILURE);
	}
	open_files(argc, argv);
	pathlist = getpathlist(envp, "PATH=");
	if (!pathlist)
	{
		ft_putendl_fd("Error: Can't find path list", 2);
		// close_all(fds);
		exit (EXIT_FAILURE);
	}
	pipex(argc - 3, argv, pathlist);
	ft_free_tab((void **)pathlist);
	return (0);
}
