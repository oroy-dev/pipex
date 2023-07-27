/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:12:08 by oroy              #+#    #+#             */
/*   Updated: 2023/07/27 15:35:07 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free (ptr);
		ptr = NULL;
	}
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free (tab[i]);
			i++;
		}
		tab = NULL;
	}
}

void	free_data(void)
{
	t_data	*pipex;

	pipex = get_data();
	ft_free_tab(pipex->cmd);
	ft_free(pipex->cmdpath);
	ft_free(pipex->files);
	ft_free_tab(pipex->pathlist);
	ft_free(pipex->pipes);
	ft_free(pipex);
}
