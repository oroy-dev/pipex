/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/12 12:05:33 by oroy             ###   ########.fr       */
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

// void	parent_process(int fd_out, int *fds)
// {
// 	char	*argvec2[] = {"wc", "-w", NULL};

// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[1]);
// 	execve ("usr/bin/wc", argvec2, NULL);
// }

// void	child_process(int fd_in, int *fds)
// {
// 	char	*argvec[] = {"ls", "-l", NULL};

// 	dup2(fds[0], STDIN_FILENO);
// 	dup2(fd_in, STDOUT_FILENO);
// 	close(fd[0]);
// 	execve ("/bin/ls", argvec, NULL);
// }

void	pipex(int fd_in, int fd_out)
{
	int		fds[2];
	pid_t	pid1;
	char	*argvec[] = {"cat", NULL};
	char	*argvec2[] = {"grep", "libft", NULL};
	
	if (pipe (fds) == -1)
		exit (EXIT_FAILURE);
	pid1 = fork ();
	if (pid1 == -1)
		exit (EXIT_FAILURE);
	if (!pid1)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		execve ("/bin/cat", argvec, NULL);
		exit (EXIT_SUCCESS);
	}
	waitpid (pid1, NULL, 0);
	dup2(fds[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fds[1]);
	execve ("/usr/bin/grep", argvec2, NULL);
}

int	main(void)
{
	int	fd_in;
	int	fd_out;

	fd_in = open ("infile.txt", O_RDONLY);
	fd_out = open ("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in < 0 || fd_out < 0)
	{
		ft_printf ("Can't open input and output files");
		return (1);
	}
	else
		pipex(fd_in, fd_out);
	return (0);
}
