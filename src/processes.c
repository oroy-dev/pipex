/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:32 by oroy              #+#    #+#             */
/*   Updated: 2023/08/02 15:40:38 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(int remaining_cmds, int argc, char **argv)
{
	t_data	*pipex;

	pipex = get_data();
	if (!pipex->files[0])
		open_infile(argv);
	dup2_(pipex->files[0], STDIN_FILENO);
	if (remaining_cmds > 1)
		dup2_(pipex->pipes[1], STDOUT_FILENO);
	else
	{
		open_outfile(argc, argv);
		dup2_(pipex->files[1], STDOUT_FILENO);
	}
	close_all();
	execve_(pipex->cmdpath, pipex->cmd, NULL);
}

void	execute_cmds(int remaining_cmds, int argc, char **argv)
{
	t_data	*pipex;
	pid_t	process;

	pipex = get_data();
	while (remaining_cmds)
	{
		get_cmd_info(argv[argc - remaining_cmds - 1]);
		if (remaining_cmds - 1)
			pipe_(pipex->pipes);
		process = fork_();
		if (process == 0)
			child_process(remaining_cmds, argc, argv);
		waitpid_(process, NULL, 0);
		if (remaining_cmds - 1)
		{
			if (!pipex->files[0])
				pipex->files[0] = dup_(pipex->pipes[0]);
			else
				dup2_(pipex->pipes[0], pipex->files[0]);
			close_fds(pipex->pipes);
		}
		ft_free_tab(pipex->cmd);
		ft_free(pipex->cmdpath);
		remaining_cmds--;
	}
}
