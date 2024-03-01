/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:15:35 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/01 20:34:18 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first(t_pipex *pipex, char *cmd)
{
	pipe(pipex->command.fd_pipe_out);
	pipex->pid[0] = fork();
	if (pipex->pid[0] == 0)
		exit(exec_child(*pipex, cmd, FIRST));
}

void	exec_mid(t_pipex *pipex, char *cmd)
{
	while (pipex->command_iter < pipex->argc - 2)
	{
		if (pipex->command_iter > 3)
			close_pipe(pipex->command.fd_pipe_in);
		cpy_pipe(pipex->command.fd_pipe_in, pipex->command.fd_pipe_out);
		pipe(pipex->command.fd_pipe_out);
		pipex->pid[pipex->command_iter - 2] = fork();
		if (pipex->pid[pipex->command_iter - 2] == 0)
			exit(exec_child(*pipex, cmd, MID));
		pipex->command_iter++;
	}
}

void	exec_last(t_pipex *pipex, char *cmd)
{
	if (pipex->argc - 3 > 2)
		close_pipe(pipex->command.fd_pipe_in);
	cpy_pipe(&pipex->command.fd_pipe_in, pipex->command.fd_pipe_out);
	pipex->pid[pipex->command_iter - 2] = fork();
	if (pipex->pid[pipex->command_iter - 2] == 0)
		exit(exec_child(*pipex, cmd, LAST));
}

int	exec_child(t_pipex pipex, char *cmd, int type)
{
	free(pipex.pid);
	pipex.command.command = cmd;
	pipex.command.type = type;
	return (exec_process(pipex.command, pipex.path));
}
