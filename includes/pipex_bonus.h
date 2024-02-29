/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:41:35 by cnatanae          #+#    #+#             */
/*   Updated: 2024/02/29 10:53:14 by cnatanae         ###   ########.fr       */
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

/*
 * @brief Enum for file type
 * @details Enum for utility functions where the file type is important
 * @param IN: input file
 * @param OUT: output file
 * @param ERROR: error file
*/
typedef enum e_file_type
{
	IN,
	OUT,
	ERROR,
}	t_file_type;

/*
 * @brief Enum for exit type
 * @details Enum for utility functions where the type exit is important
 * @param SUCCESS: success
 * @param FAILURE: failure
*/
typedef enum e_exit_type
{
	SUCCESS,
	FAILURE,
}	t_exit_type;

int		full_error(char *str1, char *str2, char *str3, unsigned int retrn);
void	usage_error(void);
char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);
void	child_process(char *argv, char **envp);
int		open_file(char *argv, int i);
void	here_doc(char *limiter, int argc);
int		mini_gnl(char **line);

#endif