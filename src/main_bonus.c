/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:56:26 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/01 18:59:05 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*join_paths(char *absolute, char *relative)
{
	char	total_size;
	int		absolute_size;
	char	*str;

	absolute_size = ft_strlen(absolute);
	if (absolute[absolute_size - 1] == '/')
		absolute_size--;
	if (relative[0] == '/')
		relative++;
	total_size = absolute_size + ft_strlen(relative) + 2;
	str = malloc(total_size);
	ft_strlcpy(str, absolute, total_size);
	str[absolute_size] = '/';
	str[absolute_size + 1] = '\0';
	ft_strlcat(str, relative, total_size);
	return (str);
}

t_path	get_path_variables(char **envp)
{
	int		i;
	t_path	path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			path.path = get_split(envp[i]);
		else if (ft_strncmp(envp[i], "PWD", 3) == 0)
			path.pwd = ft_strdup(ft_strchr(envp[i], '=') + 1);
		else if (ft_strncmp(envp[i], "HOME", 3) == 0)
			path.home = ft_strdup(ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (path);
}

char	*get_command_from_path(char *cmd, t_path path)
{
	char	*new_command;

	new_command = NULL;
	if (ft_strchr(cmd, '/') == NULL && cmd[0] != '~')
	{
		for (int i = 0; path.path[i]; i++)
		{
			new_command = join_paths(path.path[i], cmd);
			if (access(new_command, F_OK | X_OK) == 0)
				break ;
			free(new_command);
			new_command = NULL;
		}
	}
	else
	{
		if (cmd[0] == '/')
			new_command = ft_strdup(cmd);
		else if (cmd[0] == '~')
		{
			if (cmd[1] == '/')
				new_command = join_paths(path.home, cmd + 2);
			else
				new_command = join_paths(path.home, cmd + 1);
		}
		else if (ft_strncmp(cmd, "./", 2) == 0)
			new_command = join_paths(path.pwd, cmd + 2);
		else
			new_command = join_paths(path.pwd, cmd);
	}
	return (new_command);
}

int	exec_proc(t_command command, t_path path)
{
	int		return_code;
	char	*command_absolute;
	char	**command_split;

	command_split = ft_split(command.command, ' ');
	command_absolute = get_command_from_path(command_split[0], path);

	if (command.type == FIRST)
	{
		dup2(command.fd_file_in, STDIN_FILENO);
		dup2(command.fd_pipe_out[WRITE], STDOUT_FILENO);

		close(command.fd_file_in);
		close(command.fd_file_out);
		close_pipe(command.fd_pipe_out);
	}
	else if (command.type == MID)
	{
		dup2(command.fd_pipe_in[READ], STDIN_FILENO);
		dup2(command.fd_pipe_out[WRITE], STDOUT_FILENO);

		close(command.fd_file_in);
		close(command.fd_file_out);
		close_pipe(command.fd_pipe_in);
		close_pipe(command.fd_pipe_out);
	}

	else
	{
		dup2(command.fd_pipe_in[READ], STDIN_FILENO);
		dup2(command.fd_file_out, STDOUT_FILENO);

		close(command.fd_file_in);
		close(command.fd_file_out);
		close_pipe(command.fd_pipe_in);
	}

	if (command_absolute && access(command_absolute, F_OK | X_OK) == 0)
		execve(command_absolute, command_split, command.envp);

	perror(command_absolute);

	if (!command_absolute || access(command_absolute, F_OK) != 0)
		return_code = 127;
	else if (access(command_absolute, X_OK) != 0)
		return_code = 126;
	else
		return_code = 1;

	free_split(command_split);
	if (command_absolute)
		free(command_absolute);
	free(path.home);
	free(path.pwd);
	free_split(path.path);
	return (return_code);
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, "Usage error.\nExpected: ./pipex <file_in> <cmd1> ... <cmdn> <file_out>\n", 70);
		exit(1);
	}
	pipex->command.fd_file_in = open(argv[1], O_RDONLY);
	if (pipex->command.fd_file_in < 0)
		perror("Invalid input file");
	pipex->command.fd_file_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->command.fd_file_out < 0)
		perror("Invalid output file");
	pipex->path = get_path_variables(envp);
	pipex->command_iter = 3;
	pipex->command.envp = envp;
	pipex->pid = malloc(sizeof(int) * (argc - 3));
}

int	exec_child(t_pipex pipex, char *cmd, int type)
{
	free(pipex.pid);
	pipex.command.command = cmd;
	pipex.command.type = type;
	return (exec_proc(pipex.command, pipex.path));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	// if (argc < 5)
	// {
	// 	write(2, "Usage error.\nExpected: ./pipex <file_in> <cmd1> ... <cmdn> <file_out>\n", 70);
	// 	return (1);
	// }
	// command.fd_file_in = open(argv[1], O_RDONLY);
	// if (command.fd_file_in < 0)
	// 	perror("Invalid input file");
	// command.fd_file_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (command.fd_file_out < 0)
	// 	perror("Invalid output file");
	// path = get_path_variables(envp);
	// command_iter = 3;
	// command.envp = envp;
	// pid = malloc(sizeof(int) * (argc - 3));

	init_pipex(&pipex, argc, argv, envp);

	// First cmd

	pipe(pipex.command.fd_pipe_out);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
	{
		// free(pid);
		// command.command = argv[2];
		// command.type = FIRST;
		// return (exec_proc(command, path));
		return (exec_child(pipex, argv[2], FIRST));
	}

	// Mid cmd

	while (pipex.command_iter < argc - 2)
	{
		if (pipex.command_iter > 3)
			close_pipe(pipex.command.fd_pipe_in);
		ft_memcpy(pipex.command.fd_pipe_in, pipex.command.fd_pipe_out, sizeof(int) * 2);
		// cpy_pipe(pipex.command.fd_pipe_in, pipex.command.fd_pipe_out);
		pipe(pipex.command.fd_pipe_out);
		pipex.pid[pipex.command_iter - 2] = fork();
		if (pipex.pid[pipex.command_iter - 2] == 0)
		{
			// free(pipex.pid);
			// pipex.command.command = argv[pipex.command_iter];
			// return (exec_proc(pipex.command, pipex.path));
			return (exec_child(pipex, argv[pipex.command_iter], MID));
		}
		pipex.command_iter++;
	}

	//Last cmd

	if (argc - 3 > 2)
		close_pipe(pipex.command.fd_pipe_in);
	ft_memcpy(pipex.command.fd_pipe_in, pipex.command.fd_pipe_out, sizeof(int) * 2);
	// cpy_pipe(&pipex.command.fd_pipe_in, pipex.command.fd_pipe_out);
	pipex.pid[pipex.command_iter - 2] = fork();
	if (pipex.pid[pipex.command_iter - 2] == 0)
	{
		// free(pipex.pid);
		// pipex.command.command = argv[pipex.command_iter];
		// return (exec_proc(pipex.command, pipex.path));
		return (exec_child(pipex, argv[pipex.command_iter], LAST));
	}

	// Wait cmd's
	close_pipe(pipex.command.fd_pipe_in);
	close(pipex.command.fd_file_in);
	close(pipex.command.fd_file_out);
	pipex.command_iter = 0;
	while (pipex.command_iter < (argc - 3))
	{
		waitpid(pipex.pid[pipex.command_iter], &pipex.return_code, 0);
		pipex.command_iter++;
	}
	free(pipex.pid);
	free(pipex.path.home);
	free(pipex.path.pwd);
	free_split(pipex.path.path);
	return ((pipex.return_code >> 8) & 0xFF);
}
