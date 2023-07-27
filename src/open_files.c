/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:42:54 by oroy              #+#    #+#             */
/*   Updated: 2023/07/27 12:59:17 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	open_files(int argc, char **argv)
{
	t_data	*pipex;

	pipex = get_data();
	pipex->files = ft_calloc(2, sizeof (int));
	malloc_check(pipex->files);
	pipex->files[0] = open (argv[1], O_RDONLY);
	if (pipex->files[0] == -1)
	{
		perror ("Can't open infile");
		free_data();
		exit (EXIT_FAILURE);
	}
	pipex->files[1] = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->files[1] == -1)
	{
		perror ("Can't open/create outfile");
		close_(pipex->files[0]);
		free_data();
		exit (EXIT_FAILURE);
	}
}
