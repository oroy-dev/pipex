/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:38:19 by oroy              #+#    #+#             */
/*   Updated: 2023/07/21 19:51:22 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_fildes
{
	int	files[2];
	int	pipes[2];
}	t_fildes;

void	close_(int fildes);
void	close_fds(int num_args, ...);
void	dup2_(int fildes, int fildes2);
void	execve_(const char *path, char *const argv[], char *const envp[]);
void	ft_free(void *ptr);
pid_t	fork_(void);
void	null_check(void *nul);
void	pipe_(int fildes[2]);
void	waitpid_(pid_t pid, int *status, int options);

#endif
