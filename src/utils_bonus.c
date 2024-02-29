/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:40:44 by cnatanae          #+#    #+#             */
/*   Updated: 2024/02/29 11:02:14 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	full_error(char *str1, char *str2, char *str3, unsigned int retrn)
{
	ft_putstr_fd("Pipex: ", ERROR);
	ft_putstr_fd(str1, ERROR);
	ft_putstr_fd(str2, ERROR);
	ft_putendl_fd(str3, ERROR);
	return (retrn);
}

void	usage_error(void)
{
	ft_putstr_fd("Error: Bad argument\n", ERROR);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", ERROR);
	ft_putstr_fd("Or: ", ERROR);
	ft_putendl_fd("./pipex \"here_doc\" <LIMITER> <cmd1> <...> <file>", ERROR);
	exit(EXIT_SUCCESS);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		return (full_error("File error: ", argv, strerror(errno), 1));
	return (file);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		ft_putendl_fd("Pipex: Command not found: ", ERROR);
		ft_putendl_fd(cmd[0], ERROR);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_putendl_fd("Pipex: Execution error: ", ERROR);
		exit(EXIT_FAILURE);
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
