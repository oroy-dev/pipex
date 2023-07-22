/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/21 17:43:47 by oroy             ###   ########.fr       */
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
		null_check(path);
		if (access (path, X_OK) == 0)
			return (path);
		ft_free(path);
		i++;
	}
	return (NULL);
}

static void	exec_cmd(int in, int out, char *arg, char **pathlist)
{
	char	**cmd;
	char	*path;
	size_t	i;

	i = 0;
	dup2_(out, STDOUT_FILENO);
	close_(in);
	cmd = ft_split(arg, ' ');
	null_check(cmd);
	path = ft_strjoin("/", cmd[0]);
	null_check(path);
	path = path_to_exec(pathlist, path);
	if (!path)
	{
		ft_putstr_fd("Error: Shell Command Not Executable", 2);
		exit (EXIT_FAILURE);
	}
	execve_(path, cmd, NULL);
	while (cmd[i])
	{
		ft_free(cmd[i]);
		i++;
	}
	ft_free(path);
	close_(out);
}

static void	pipex(int files[2], char **argv, char **pathlist, int count)
{
	int		pipes[2];
	pid_t	process;
	int		status;
	int		i;

	i = 0;
	while (i < count)
	{
		pipe_(pipes);
		process = fork_();
		if (process == 0)
		{
			dup2_(files[INFILE], STDIN_FILENO);
			exec_cmd(pipes[0], pipes[1], argv[i + 2], pathlist);
			exit (EXIT_SUCCESS);
		}
		waitpid_(process, &status, 0);
		dup2_(pipes[0], files[INFILE]);
		close_(pipes[1]);
		i++;
	}
	dup2_(pipes[0], STDIN_FILENO);
	exec_cmd(files[INFILE], files[OUTFILE], argv[i + 2], pathlist);
	ft_free(pathlist);
}

static char	**getpathlist(char **envp, char *path, int files[2])
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
			null_check(pathstr);
			pathlist = ft_split(pathstr, ':');
			ft_free(pathstr);
			null_check(pathlist);
			return (pathlist);
		}
		i++;
	}
	ft_putstr_fd("Error: Can't find path list\n", 2);
	close_(files[INFILE]);
	close_(files[OUTFILE]);
	exit (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	

	if (argc < 5)
	{
		ft_putstr_fd("Error: Lower number of arguments than required\n", 2);
		exit (EXIT_FAILURE);
	}
	files[INFILE] = open (argv[1], O_RDONLY);
	if (files[INFILE] == -1)
	{
		perror ("Can't open infile");
		exit (EXIT_FAILURE);
	}
	files[OUTFILE] = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files[OUTFILE] == -1)
	{
		perror ("Can't open/create outfile");
		close_(files[INFILE]);
		exit (EXIT_FAILURE);
	}
	pathlist = getpathlist(envp, "PATH=", files);
	pipex(files, argv, pathlist, argc - 4);
	return (0);
}