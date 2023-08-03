/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_dup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/08/02 15:06:12 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	dup_(int fildes)
{
	int	fildes2;

	fildes2 = dup (fildes);
	if (fildes2 == -1)
	{
		perror ("Problem with dup2() call");
		close_all();
		free_data();
		exit (EXIT_FAILURE);
	}
	return (fildes2);
}

void	dup2_(int fildes, int fildes2)
{
	if (dup2 (fildes, fildes2) == -1)
	{
		perror ("Problem with dup2() call");
		close_all();
		free_data();
		exit (EXIT_FAILURE);
	}
}
