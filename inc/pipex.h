/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:38:19 by oroy              #+#    #+#             */
/*   Updated: 2023/07/24 16:53:59 by oroy             ###   ########.fr       */
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
void	execve_(char *path, char **cmd, char **envp, int fds[2][2]);
void	ft_free(void *ptr);
void	ft_free_tab(void **tab);
pid_t	fork_(int fds[2][2]);
void	malloc_check(void *maloc, int fds[2][2]);
void	pipe_(int fds[2][2]);
void	waitpid_(pid_t pid, int *status, int options);

#endif
