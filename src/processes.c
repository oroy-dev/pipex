/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:32 by oroy              #+#    #+#             */
/*   Updated: 2023/07/27 15:35:40 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(int remaining_cmds)
{
	t_data	*pipex;

	pipex = get_data();
	dup2_(pipex->files[0], STDIN_FILENO);
	if (remaining_cmds > 1)
	{
		dup2_(pipex->pipes[1], STDOUT_FILENO);
		close_all();
	}
	else
	{
		dup2_(pipex->files[1], STDOUT_FILENO);
		close_(pipex->files[0]);
		close_(pipex->files[1]);
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
	pipex->pipes = ft_calloc(2, sizeof (int));
	malloc_check(pipex->pipes);
	while (--remaining_cmds)
	{
		get_cmd_info(argv[argc - remaining_cmds - 1]);
		if (remaining_cmds - 1)
			pipe_(pipex->pipes);
		process = fork_();
		if (process == 0)
			child_process(remaining_cmds);
		waitpid_(process, &status, 0);
		if (remaining_cmds - 1)
		{
			dup2_(pipex->pipes[0], pipex->files[0]);
			close_(pipex->pipes[0]);
			close_(pipex->pipes[1]);
		}
		ft_free_tab(pipex->cmd);
		ft_free(pipex->cmdpath);
	}
}
