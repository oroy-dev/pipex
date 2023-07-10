/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/10 18:32:46 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// int	main(int argc, char **argv)
// {
// 	char	*cmd;
// 	size_t	i;

// 	cmd = NULL;
// 	if (argc > 1)
// 	{
// 		i = 1;
// 		cmd = ft_strdup(" < ");
// 		while (argv[i])
// 		{
// 			cmd = ft_strjoin(cmd, argv[i]);
// 			if (i == 1)
// 				cmd = ft_strjoin(cmd, " ");
// 			else if (i == 2)
// 				cmd = ft_strjoin(cmd, " | ");
// 			else if (i == 3)
// 				cmd = ft_strjoin(cmd, " > ");
// 			i++;
// 		}
// 		printf ("%s\n", cmd);
// 	}
// 	return (0);
// }

void	pipex(int fd_in, int fd_out, char **argv)
{
	int		fd[2];
	pid_t	pid1;
	char	*argvec[] = {"ls", "-l", NULL};
	char	*argvec2[] = {"wc", "-w", NULL};

	if (pipe (fd) == -1)
		exit (1);
	pid1 = fork ();
	if (pid1 == -1)
		exit (1);
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve ("/bin/ls", argvec, NULL);
	}
	waitpid (pid1, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execve ("usr/bin/wc", argvec2, NULL);
}

int	main(int argc, char **argv)
{
	int	fd_in;
	int	fd_out;

	fd_in = open ("infile.txt", O_RDONLY);
	fd_out = open ("outfile.txt", O_WRONLY);
	if (fd_in < 0 || fd_out < 0)
		return (1);
	else
		pipex(fd_in, fd_out, argv, envp);
	return (0);
}
