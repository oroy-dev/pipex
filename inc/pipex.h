/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:38:19 by oroy              #+#    #+#             */
/*   Updated: 2023/07/25 13:56:59 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_fds
{
	int	files[2];
	int	pipes[2];
}	t_fds;

t_fds	*get_fds(void);
void	close_(int fildes);
void	close_all();
void	dup2_(int fildes, int fildes2);
void	execve_(char *path, char **cmd, char **envp);
void	ft_free(void *ptr);
void	ft_free_tab(void **tab);
pid_t	fork_();
void	malloc_check(void *maloc);
void	pipe_();
void	waitpid_(pid_t pid, int *status, int options);

#endif
