/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:14:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:20:06 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_internal(t_philo *philo, t_state state);
static void	write_status_debug(t_philo *philo, t_state state);

void	write_status(t_philo *philo, t_state state)
{
	if (DEBUG == 1)
		write_status_debug(philo, state);
	else
		write_status_internal(philo, state);
}

static void	write_status_internal(t_philo *philo, t_state state)
{
	t_table	*table;
	t_ull	timestamp;

	table = philo->table;
	timestamp = now_in_ms() - table->times.start_time;
	pthread_mutex_lock(&philo->write_mutex);
	if ((state == TAKEN_FORK || state == TAKEN_SECOND_FORK)
		&& !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d has taken a fork\n", timestamp, philo->id);
	else if (state == EATING && !simulation_finished(table))
		printf(WHITE"%llu"CYAN" %d is eating"RESET"\n", timestamp, philo->id);
	else if (state == THINKING && !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d is thinking\n", timestamp, philo->id);
	else if (state == SLEEPING && !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d is sleeping\n", timestamp, philo->id);
	else if (state == DEAD)
		printf(WHITE"%llu"RED" %d died"RESET"\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->write_mutex);
}

static void	write_status_debug(t_philo *philo, t_state state)
{
	t_table	*table;
	t_ull	timestamp;
	int		meals_eaten;

	table = philo->table;
	timestamp = now_in_ms() - table->times.start_time;
	meals_eaten = get_int(&philo->meal_mutex, &philo->meals_eaten);
	pthread_mutex_lock(&philo->write_mutex);
	if (state == TAKEN_FORK && !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d has taken the first fork🍴 "MAGENTA"[Fork ID: %d]"RESET"\n",
		 timestamp, philo->id, philo->first_fork->id);
	else if (state == TAKEN_SECOND_FORK && !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d has taken the second fork🍴 "MAGENTA"[Fork ID: %d]"RESET"\n",
		 timestamp, philo->id, philo->second_fork->id);
	else if (state == EATING && !simulation_finished(table))
		printf(WHITE"%llu"CYAN" %d is eating 🍝 "MAGENTA"[Meals eaten: %d]"RESET"\n",
		 timestamp, philo->id, meals_eaten);
	else if (state == THINKING && !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d is thinking\n", timestamp, philo->id);
	else if (state == SLEEPING && !simulation_finished(table))
		printf(WHITE"%llu"RESET" %d is sleeping\n", timestamp, philo->id);
	else if (state == DEAD)
		printf(WHITE"%llu"RED"💀💀 %d died 💀💀"RESET"\n", timestamp, philo->id);
	else if (state == FULL)
		printf(GREEN"[DEBUG] 🐷🐷 Full philosopher found, stopping threads... 🐷🐷 "RESET
			"[Philosopher ID: %d - Meals Eaten: %d]\n", philo->id, philo->meals_eaten);
	pthread_mutex_unlock(&philo->write_mutex);
}
