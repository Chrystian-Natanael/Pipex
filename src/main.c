/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:32:26 by cnatanae          #+#    #+#             */
/*   Updated: 2024/02/19 17:16:59 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	full_error(char *str1, char *str2, char *str3, unsigned int retrn)
{
	ft_putstr_fd("Pipex: ", ERROR);
	ft_putstr_fd(str1, ERROR);
	ft_putstr_fd(str2, ERROR);
	ft_putstr_fd(str3, ERROR);
	ft_putstr_fd("\n", ERROR);
	exit (retrn);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	structure;

	if (argc < 5)
		return (full_error("Too few arguments", "", "", FAILURE));
	structure.fd_in = open(argv[1], O_RDONLY);
	structure.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (structure.fd_in == -1)
		return (full_error("Error opening file ", argv[1], "", FAILURE));
	else if (structure.fd_out == -1)
		return (full_error("Error opening file ", argv[argc - 1], "", FAILURE));
	pipe(structure.fd);
	structure.pid[0] = fork();
	if (structure.pid[0] < 0)
		return (full_error("Error creating child process", "PID[0]", "", FAILURE));

// !		Process children

	if (structure.pid[0] == 0)
	{
		// fecha os q nn vai usar
		close(structure.fd[0]);
		close(structure.fd_out);

		// pega o primeiro comando, separando por ' '
		structure.cmd1 = ft_split(argv[2], ' ');

		// redireciona o input para o arquivo
		dup2(structure.fd_in, STDIN_FILENO);
		dup2(structure.fd[1], STDOUT_FILENO);

		// fecha o arquivo e a ponta do pipe que nn vai usar
		close(structure.fd_in);
		close(structure.fd[1]);

		// executa o comando
	}

// !		Process parent

	if (structure.pid[0] > 0)
	{
		int	status;

		// espera o filho terminar
		waitpid(-1, &status, 0);

		// redireciona o input para o arquivo
		dup2(structure.fd_out, STDOUT_FILENO);
		dup2(structure.fd[1], STDIN_FILENO);

		// fecha o arquivo e a ponta do pipe que nn vai usar
		close(structure.fd_out);
		close(structure.fd[0]);
		// execve here
	}
	return (0);
}
