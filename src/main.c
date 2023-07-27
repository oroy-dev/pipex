/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2023/07/27 16:15:48 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*pipex;

	if (argc < 5)
	{
		ft_putendl_fd("Error: Lower number of arguments than required", 2);
		exit (EXIT_FAILURE);
	}
	pipex = get_data();
	open_files(argc, argv);
	get_pathlist(envp, "PATH=");
	start_execution(argc - 2, argc, argv);
	close_(pipex->files[0]);
	close_(pipex->files[1]);
	ft_free(pipex->files);
	ft_free_tab(pipex->pathlist);
	ft_free(pipex->pipes);
	// free_data();
	return (0);
}
