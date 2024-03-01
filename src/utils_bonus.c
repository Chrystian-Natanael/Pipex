/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:28:13 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/01 20:27:21 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipe(int *fd_pipe)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

char	**split_path(char *str)
{
	char	*start;
	char	**split;

	start = ft_strchr(str, '=') + 1;
	split = ft_split(start, ':');
	return (split);
}

void	cpy_pipe(void *pipe_in, void *pipe_out)
{
	ft_memcpy(pipe_in, pipe_out, sizeof(int) * 2);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split && split[++i])
		free(split[i]);
	free(split);
}

void	close_wait_free(t_pipex *pipex)
{
	close_pipe(pipex->command.fd_pipe_in);
	if (pipex->command.fd_file_in != -1)
		close(pipex->command.fd_file_in);
	if (pipex->command.fd_file_out != -1)
		close(pipex->command.fd_file_out);
	pipex->command_iter = 0;
	while (pipex->command_iter < (pipex->argc - 3))
	{
		waitpid(pipex->pid[pipex->command_iter], &pipex->return_code, 0);
		pipex->command_iter++;
	}
	free(pipex->pid);
	free(pipex->path.home);
	free(pipex->path.pwd);
	free_split(pipex->path.path);
}
