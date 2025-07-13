/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:36:32 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/10 22:46:33 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(int c);
static bool	ft_isspace(int c);

void	exit_error(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *nptr)
{
	int		nbr;
	int		sign;
	size_t	i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * sign);
}

bool	is_valid_number(char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (false);
	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	else
		return (false);
}

static bool	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (true);
	else
		return (false);
}
