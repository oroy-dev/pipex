/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:32 by oroy              #+#    #+#             */
/*   Updated: 2023/08/01 14:08:45 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(int remaining_cmds, int argc, char **argv)
{
	t_data	*pipex;

	pipex = get_data();
	if (!pipex->savedpipe)
	{
		open_infile(argv);
		dup2_(pipex->files[0], STDIN_FILENO);
	}
	else
	{
		dup2_(pipex->savedpipe, STDIN_FILENO);
		close_(pipex->savedpipe);
	}
	if (remaining_cmds > 1)
	{
		dup2_(pipex->pipes[1], STDOUT_FILENO);
		close_all();
	}
	else
	{
		open_outfile(argc, argv);
		dup2_(pipex->files[1], STDOUT_FILENO);
		close_files();
	}
	execve_(pipex->cmdpath, pipex->cmd, NULL);
	exit (EXIT_FAILURE);
}

void	start_execution(int remaining_cmds, int argc, char **argv)
{
	t_data	*pipex;
	pid_t	process;
	int		status;

	pipex = get_data();
	while (--remaining_cmds)
	{
		get_cmd_info(argv[argc - remaining_cmds - 1]);
		if (remaining_cmds - 1)
			pipe_(pipex->pipes);
		process = fork_();
		if (process == 0)
			child_process(remaining_cmds, argc, argv);
		waitpid_(process, &status, 0);
		if (remaining_cmds - 1)
		{
			pipex->savedpipe = dup (pipex->pipes[0]);
			close_pipes();
		}
		ft_free_tab(pipex->cmd);
		ft_free(pipex->cmdpath);
	}
	close_(pipex->savedpipe);
}
