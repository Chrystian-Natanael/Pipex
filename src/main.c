/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:26 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/04 07:26:27 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_command(char *command, char **envp)
{
	char	**cmd;
	char	*path_cmd;
	int		ret_code;

	ret_code = 0;
	cmd = ft_split(command, ' ');
	if (cmd == NULL)
		return (full_error("split error\n", "", "", 1));
	path_cmd = get_path_cmd(cmd[0], envp);
	execve(path_cmd, cmd, envp);
	if (access(path_cmd, F_OK) != 0)
	{
		ft_putstr_fd("pipex: ", ERROR);
		ft_putstr_fd(cmd[0], ERROR);
		ft_putendl_fd(": command not found", ERROR);
		ret_code = 127;
	}
	else if (access(path_cmd, X_OK | F_OK) != 0)
		ret_code = full_error("permission denied: ", "", "", 126);
	free(path_cmd);
	free_split(cmd);
	close(0);
	close(1);
	close(2);
	return (ret_code);
}

int	child_process(int *fd, char **argv, char **envp)
{
	int	file_in;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1 || access(argv[1], F_OK) != 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (full_error(argv[1], ": No such file or directory", "", 1));
	}
	dup2(file_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_in);
	return (execute_command(argv[2], envp));
}

int	parent_process(int *fd, char **argv, char **envp)
{
	int	file_out;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (full_error("File error: ", argv[4], "", 1));
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_out);
	return (execute_command(argv[3], envp));
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;

	if (argc == 5)
	{
		pipe(fd);
		pid[0] = fork();
		if (pid[0] == -1)
			return (full_error("Fork error\n", "", "", 1));
		if (pid[0] == 0)
			return (child_process(fd, argv, envp));
		pid[1] = fork();
		if (pid[1] == 0)
			return (parent_process(fd, argv, envp));
		close(fd[0]);
		close(fd[1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], &status, 0);
		return ((status >> 8) & 0xFF);
	}
	else
		return (full_error("Invalid number of arguments\n", "Try use: ", \
			"./pipex <file1> <cmd1> <cmd2> <file2>\n", 1));
	return (1);
}
