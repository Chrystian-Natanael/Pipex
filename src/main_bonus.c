/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:40:41 by cnatanae          #+#    #+#             */
/*   Updated: 2024/02/29 11:05:01 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		full_error("Pipe error: ", strerror(errno), "", 1);
	pid = fork();
	if (pid == -1)
		full_error("Fork error: ", strerror(errno), "", 1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute(argv, envp);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage_error();
	if (pipe(fd) == -1)
		full_error("Pipe error: ", strerror(errno), "", 1);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (mini_gnl(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	mini_gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

int  main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);	
	}
	usage_error();
}
