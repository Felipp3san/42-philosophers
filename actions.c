/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/10 19:34:28 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_dead(t_philo *philo)
{
	if (now_in_ms() - philo->last_meal_time > philo->params->time_to_die)
		return (TRUE);
	else
		return (FALSE);
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if (is_dead(philo))
	{
		printf("%zu %d died\n", now_in_ms(), philo->id);
		philo->is_alive = FALSE;
	}
	else
	{
		printf("%zu %d has taken a fork\n", now_in_ms(), philo->id);
		printf("%zu %d is eating\n", now_in_ms(), philo->id);
		usleep(msec_to_usec(philo->params->time_to_eat));
		philo->last_meal_time = now_in_ms();
	}
	pthread_mutex_unlock(philo->mutex);
}

void	p_think(t_philo *philo)
{
	printf("%zu %d is thinking\n", now_in_ms(), philo->id);
}

void	p_sleep(t_philo *philo)
{
	printf("%zu %d is sleeping\n", now_in_ms(), philo->id);
	usleep(msec_to_usec(philo->params->time_to_sleep));
}
