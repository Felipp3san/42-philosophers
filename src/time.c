/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:04:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:21:11 by fde-alme         ###   ########.fr       */
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
	t_ull	elapsed;
	t_ull	rem;

	start = now_in_usec();
	while (now_in_usec() - start < usec)
	{
		elapsed = now_in_usec() - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (now_in_usec() - start < usec)
				;
		}
	}
}
