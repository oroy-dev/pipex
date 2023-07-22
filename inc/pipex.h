/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:38:19 by oroy              #+#    #+#             */
/*   Updated: 2023/07/22 18:16:12 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

void	close_(int fildes);
void	close_all_fds(int fds[2][2]);
void	dup2_(int fildes, int fildes2, int fds[2][2]);
void	execve_(const char *path, char *const argv[], char *const envp[]);
void	ft_free(void *ptr);
pid_t	fork_(int fds[2][2]);
void	malloc_check(void *maloc, int fds[2][2]);
void	pipe_(int fds[2][2]);
void	waitpid_(pid_t pid, int *status, int options);

#endif
