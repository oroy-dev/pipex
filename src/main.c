/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:22:26 by oroy              #+#    #+#             */
/*   Updated: 2024/12/08 23:34:15 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putendl_fd("Error: Lower number of arguments than required (5)", 2);
		exit (EXIT_FAILURE);
	}
	get_pathlist(envp, "PATH=");
	execute_cmds(argc - 3, argc, argv);
	close_all();
	free_data();
	return (0);
}
