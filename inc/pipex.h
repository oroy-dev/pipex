/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:38:19 by oroy              #+#    #+#             */
/*   Updated: 2023/08/04 14:38:09 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**cmd;
	char	*cmdpath;
	int		files[2];
	char	**pathlist;
	int		pipes[2];
}	t_data;

void	close_(int fildes);
void	close_all(void);
void	close_tab(int fildes[2]);
int		dup_(int fildes);
void	dup2_(int fildes, int fildes2);
void	execute_cmds(int remaining_cmds, int argc, char **argv);
void	execve_(char *path, char **cmd, char **envp);
pid_t	fork_(void);
void	free_data(void);
void	ft_free(void *ptr);
void	ft_free_tab(char **tab);
void	get_cmd_info(char *arg);
t_data	*get_data(void);
void	get_pathlist(char **envp, char *path);
void	malloc_check(void *maloc);
void	open_infile(char **argv);
void	open_outfile(int argc, char **argv);
void	pipe_(int fildes[2]);
void	waitpid_(pid_t pid, int *status, int options);

#endif
