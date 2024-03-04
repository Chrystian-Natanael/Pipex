/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:56:26 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/04 10:00:31 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
static int	set_dup2(t_command command);

static int	set_dup2(t_command command)
{
	int	ret_code;

	ret_code = 0;
	if (command.type == FIRST)
	{
		if (command.fd_file_in != -1)
			ret_code = dup_first(&command);
		close_pipe(command.fd_pipe_out);
	}
	else if (command.type == MID)
		ret_code = dup_mid(&command);
	else
	{
		if (command.fd_file_out != -1)
			ret_code = dup_last(&command);
		close_pipe(command.fd_pipe_in);
	}
	if (command.fd_file_in != -1)
		close(command.fd_file_in);
	if (command.fd_file_out != -1)
		close(command.fd_file_out);
	return (ret_code);
}

int	exec_process(t_command command, t_path path)
{
	int		return_code;
	char	*command_absolute;
	char	**command_split;

	command_split = NULL;
	command_absolute = NULL;
	return_code = 1;
	if (set_dup2(command))
	{
		command_split = ft_split(command.command, ' ');
		command_absolute = get_absolute_path(command_split[0], path);
		if (command_absolute && access(command_absolute, F_OK | X_OK) == 0)
			execve(command_absolute, command_split, command.envp);
		perror(command_absolute);
		if (!command_absolute || access(command_absolute, F_OK) != 0)
			return_code = 127;
		else if (access(command_absolute, X_OK) != 0)
			return_code = 126;
	}
	free_split(command_split);
	free(command_absolute);
	free(path.home);
	free(path.pwd);
	free_split(path.path);
	return (return_code);
}

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, "Usage error.\nExpected: ./pipex <file_in> <cmd1> ... \
<cmdn> <file_out>\n", 70);
		exit(1);
	}
	pipex->command.fd_file_in = open(argv[1], O_RDONLY);
	if (pipex->command.fd_file_in < 0)
		perror("Invalid input file");
	pipex->command.fd_file_out = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->command.fd_file_out < 0)
		perror("Invalid output file");
	pipex->path = get_path_variables(envp);
	pipex->command_iter = 3;
	pipex->command.envp = envp;
	pipex->argc = argc;
	pipex->pid = malloc(sizeof(int) * (argc - 3));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	init_pipex(&pipex, argc, argv, envp);
	exec_first(&pipex, argv[2]);
	exec_mid(&pipex, argv[pipex.command_iter]);
	exec_last(&pipex, argv[pipex.command_iter]);
	close_wait_free(&pipex);
	return ((pipex.return_code >> 8) & 0xFF);
}
