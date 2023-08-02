/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pathlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:43:42 by oroy              #+#    #+#             */
/*   Updated: 2023/08/02 15:05:24 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	get_pathlist(char **envp, char *path)
{
	t_data	*pipex;
	char	*pathstr;
	size_t	len;
	size_t	i;

	i = 0;
	pipex = get_data();
	while (envp[i])
	{
		if (ft_strnstr(envp[i], path, 5))
		{
			len = ft_strlen(envp[i]);
			pathstr = ft_substr(envp[i], 5, len);
			malloc_check(pathstr);
			pipex->pathlist = ft_split(pathstr, ':');
			ft_free(pathstr);
			malloc_check(pipex->pathlist);
			return ;
		}
		i++;
	}
}
