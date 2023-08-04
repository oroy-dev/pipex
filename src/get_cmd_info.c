/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:16:15 by oroy              #+#    #+#             */
/*   Updated: 2023/08/03 17:24:38 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*find_cmd_location(char **pathlist, char *cmd)
{
	char	*path;
	size_t	i;

	i = 0;
	while (pathlist[i])
	{
		path = ft_strjoin(pathlist[i], cmd);
		malloc_check(path);
		if (access (path, X_OK) == 0)
			return (path);
		ft_free(path);
		i++;
	}
	return (NULL);
}

void	get_cmd_info(char *arg)
{
	t_data	*pipex;
	char	*path;

	pipex = get_data();
	pipex->cmd = ft_split(arg, ' ');
	malloc_check(pipex->cmd);
	path = ft_strjoin("/", pipex->cmd[0]);
	malloc_check(path);
	pipex->cmdpath = find_cmd_location(pipex->pathlist, path);
	ft_free(path);
	if (!pipex->cmdpath)
	{
		ft_putstr_fd("Error: Shell command not found/executable: ", 2);
		ft_putendl_fd(arg, 2);
		free_data();
		exit (EXIT_FAILURE);
	}
}
