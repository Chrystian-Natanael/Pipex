/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:18:31 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/23 14:23:04 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char *nptr)
{
	int	idx;

	idx = 0;
	while ((nptr[idx] == '\f') || (nptr[idx] == '\n')
		|| (nptr[idx] == '\r') || (nptr[idx] == '\t')
		|| (nptr[idx] == '\v') || (nptr[idx] == ' '))
	{
		idx++;
	}
	return (idx);
}

static int	ft_odd(char c)
{
	int	odd;

	odd = 1;
	if (c == '-')
		odd = -1;
	return (odd);
}

int	ft_atoi(const char *nptr)
{
	int	odd;
	int	value;
	int	idx;

	value = 0;
	idx = ft_isspace(nptr);
	odd = ft_odd(nptr[idx]);
	if (nptr[idx] == '+' || nptr[idx] == '-')
		idx++;
	while (nptr[idx] >= '0' && nptr[idx] <= '9')
		value = value * 10 + (nptr[idx++] - '0');
	return (value * odd);
}
