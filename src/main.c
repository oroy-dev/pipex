/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/07 21:09:11 by oroy             ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	// char	*argvec[] = {"ls", "-l", NULL};
	// char	*argvec2[] = {"grep", "Makefile", NULL};

	(void) argc;
	(void) argv;
	if (pipe (fd) == -1)
		return (1);
	pid1 = fork ();
	if (pid1 == -1)
		return (1);
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		// execve ("/bin/ls", argvec, NULL);
	}
	pid2 = fork ();
	if (pid2 == -1)
		return (1);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		// execve ("usr/bin/grep", argvec2, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
