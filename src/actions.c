/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:06:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static int	safe_lock(t_mutex *mutex, t_table *table)
{
	pthread_mutex_lock(mutex);
	if (simulation_finished(table))
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	return (1);
}

static void	update_last_meal(t_philo *philo)
{
	set_ull(&philo->meal_mutex, &philo->last_meal, now_in_ms());
	increase_int(&philo->meal_mutex, &philo->meals_eaten);
}

void	p_eat(t_philo *philo)
{
	if (!safe_lock(&philo->first_fork->fork_mutex, philo->table))
		return ;
	write_status(philo, TAKEN_FORK);
	if (!safe_lock(&philo->second_fork->fork_mutex, philo->table))
	{
		pthread_mutex_unlock(&philo->first_fork->fork_mutex);
		return ;
	}
	write_status(philo, TAKEN_SECOND_FORK);
	update_last_meal(philo);
	write_status(philo, EATING);
	if (philo->meals_eaten == philo->table->meals_to_eat)
	{
		set_bool(&philo->meal_mutex, &philo->is_full, TRUE);
		write_status(philo, FULL);
	}
	ft_usleep(msec_to_usec(philo->times->time_to_eat));
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
}

void	p_think(t_philo *philo)
{
	write_status(philo, THINKING);
}

void	p_sleep(t_philo *philo)
{
	write_status(philo, SLEEPING);
	ft_usleep(msec_to_usec(philo->times->time_to_sleep));
}
