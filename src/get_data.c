/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:20:40 by oroy              #+#    #+#             */
/*   Updated: 2023/08/01 13:41:42 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_data	*get_data(void)
{
	static t_data	*pipex;

	if (!pipex)
	{
		pipex = ft_calloc(1, sizeof (t_data));
		malloc_check(pipex);
		pipex->cmd = NULL;
		pipex->cmdpath = NULL;
		pipex->pathlist = NULL;
		pipex->savedpipe = 0;
	}
	return (pipex);
}
