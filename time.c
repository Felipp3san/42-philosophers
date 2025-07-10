/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:04:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/10 19:32:37 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/types.h>

size_t	time_in_ms(struct timeval *time)
{
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

size_t	msec_to_usec(size_t time_in_ms)
{
	return (time_in_ms * 1000);
}

size_t	now_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (time_in_ms(&current_time));
}
