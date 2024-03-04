/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:01:43 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/04 10:00:43 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	dup_first(t_command *command)
{
	dup2(command->fd_file_in, STDIN_FILENO);
	dup2(command->fd_pipe_out[WRITE], STDOUT_FILENO);
	return (1);
}

int	dup_mid(t_command *command)
{
	dup2(command->fd_pipe_in[READ], STDIN_FILENO);
	dup2(command->fd_pipe_out[WRITE], STDOUT_FILENO);
	close_pipe(command->fd_pipe_in);
	close_pipe(command->fd_pipe_out);
	return (1);
}

int	dup_last(t_command *command)
{
	dup2(command->fd_file_out, STDOUT_FILENO);
	dup2(command->fd_pipe_in[READ], STDIN_FILENO);
	return (1);
}
