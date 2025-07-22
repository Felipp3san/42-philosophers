/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:25:47 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	write_status(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	write_status(philo, TAKEN_FORK);
	write_status(philo, EATING);
	set_ull(&philo->meal_mutex, &philo->last_meal, now_in_ms());
	ft_usleep(msec_to_usec(philo->times->time_to_eat));
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
	philo->meals_eaten++;
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
