/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:28:13 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/01 18:58:17 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipe(int *fd_pipe)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

char	**get_split(char *str)
{
	char	*start;
	char	**split;

	start = ft_strchr(str, '=') + 1;
	split = ft_split(start, ':');
	return (split);
}

void	cpy_pipe(int *pipe_in[2], int *pipe_out)
{
	*(pipe_in[0]) = pipe_out[0];
	*(pipe_in[1]) = pipe_out[1];
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}