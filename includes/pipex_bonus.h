/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:35 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/01 18:56:00 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// ! libft functions
# include "libft.h"

// ! both to open
# include <sys/stat.h>
# include <fcntl.h>

// ! close, read, write, access, dup, dup2, execve, fork, pipe, unlink
# include <unistd.h>

// ! malloc and free, exit
# include <stdlib.h>

// ! type libs
# include <stddef.h>
# include <sys/types.h>

// ! perror
# include <stdio.h>
# include <errno.h>

// ! strerror
# include <string.h>

// ! wait, waitpid
# include <sys/wait.h>

enum e_process
{
	FIRST = 0,
	MID,
	LAST
};

enum e_fd
{
	READ = 0,
	WRITE
};

typedef struct s_command
{
	int		type;
	int		fd_pipe_in[2];
	int		fd_pipe_out[2];
	int		fd_file_in;
	int		fd_file_out;
	char	*command;
	char	**envp;
}			t_command;

typedef struct s_path
{
	char	*home;
	char	*pwd;
	char	**path;
}			t_path;

typedef struct s_pipex
{
	t_command	command;
	t_path		path;
	int			command_iter;
	int			return_code;
	int			*pid;
}	t_pipex;


char	**get_split(char *str);
void	close_pipe(int *fd_pipe);
void	cpy_pipe(int **pipe_in, int *pipe_out);
void	free_split(char **split);

#endif