/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:04:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:31:35 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ull	time_to_msec(struct timeval *time)
{
	return ((time->tv_sec * 1e3) + (time->tv_usec / 1e3));
}

t_ull	time_to_usec(struct timeval *time)
{
	return ((time->tv_sec * 1e6) + time->tv_usec);
}

t_ull	msec_to_usec(t_ull time_in_ms)
{
	return (time_in_ms * 1000);
}

t_ull	now_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time_to_msec(&time));
}

t_ull	now_in_usec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time_to_usec(&time));
}

void	ft_usleep(t_ull usec)
{
	t_ull	start;

	start = now_in_usec();
	if (usec >= 2e3)
		usleep(usec - 1000);
	while (now_in_usec() - start < usec)
		;
}
