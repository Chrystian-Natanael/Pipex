/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:29:13 by cnatanae          #+#    #+#             */
/*   Updated: 2024/02/27 13:41:41 by cnatanae         ###   ########.fr       */
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

/* 
 * @brief Print error message and return a value
 * @details Function to concatenate error message and return a value
 * @param str1: first part of the error message
 * @param str2: second part of the error message
 * @param str3: third part of the error message
 * @param retrn: value to return
 * @return retrn
 */
int		full_error(char *str1, char *str2, char *str3, unsigned int retrn);

/*
 * @brief Fork with process the parent process
 * @details Function to fork and process the parent process
 * @param fd: file descriptor
 * @param argv: arguments
 * @param envp: environment variables
 * @return 0 if success, non 0 if failure
*/
int		parent_process(int *fd, char **argv, char **envp);

/*
 * @brief Fork with process the child process
 * @details Function to fork and process the child process
 * @param fd: file descriptor
 * @param argv: arguments
 * @param envp: environment variables
 * @return 0 if success, non 0 if failure
*/
int		child_process(int *fd, char **argv, char **envp);

/*
 * @brief Execute a command
 * @details Function to execute a command in the shell
 * @param command: command to execute
 * @param envp: environment variables
 * @return 0 if success, non 0 if failure
*/
int		execute_command(char *command, char **envp);

/*
 * @brief Get the path of a command
 * @details Function to get the path of a command and validade if it exists
 * @param cmd: command
 * @param envp: environment variables
 * @return path of the command
*/
char	*get_path_cmd(char *cmd, char **envp);

/*
 * @brief Free a split
 * @details Function to free a split of strings
 * @param split: split to free
*/
void	free_split(char **split);

#endif