/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:29:13 by cnatanae          #+#    #+#             */
/*   Updated: 2024/02/27 10:39:38 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

// ! Enum

typedef enum e_file_type
{
	IN,
	OUT,
	ERROR,
}	t_file_type;

typedef enum e_exit_type
{
	SUCCESS,
	FAILURE,
}	t_exit_type;

// ! Structs

typedef struct s_pipex
{
	int		pid[2];
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	**cmd1;
	char	**cmd2;
}	t_pipex;

// ! Functions

int		full_error(char *str1, char *str2, char *str3, unsigned int retrn);
int		parent_process(int *fd, char **argv, char **envp);
int		child_process(int *fd, char **argv, char **envp);
int		execute_command(char *command, char **envp);
char	*get_path_cmd(char *cmd, char **envp);
void	free_split(char **split);

#	endif