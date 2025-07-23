/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:14:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 12:30:15 by fde-alme         ###   ########.fr       */
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
	t_ull	ts;
	int		meals;

	ts = now_in_ms() - philo->table->times.start_time;
	meals = get_int(&philo->meal_mutex, &philo->meals_eaten);
	pthread_mutex_lock(&philo->write_mutex);
	if (state == TAKEN_FORK)
		printf(WHITE"%llu"RESET" %d took 1st fork🍴 "MAGENTA"[ID: %d]"RESET"\n",
			ts, philo->id, philo->first_fork->id);
	else if (state == TAKEN_SECOND_FORK)
		printf(WHITE"%llu"RESET" %d took 2nd fork🍴 "MAGENTA"[ID: %d]"RESET"\n",
			ts, philo->id, philo->second_fork->id);
	else if (state == EATING)
		printf(WHITE"%llu"CYAN" %d is eating 🍝 "MAGENTA"[Meals: %d]"RESET"\n",
			ts, philo->id, meals);
	else if (state == THINKING)
		printf(WHITE"%llu"RESET" %d is thinking\n", ts, philo->id);
	else if (state == SLEEPING)
		printf(WHITE"%llu"RESET" %d is sleeping\n", ts, philo->id);
	else if (state == DEAD)
		printf(WHITE"%llu"RED"💀 %d died 💀"RESET"\n", ts, philo->id);
	else if (state == FULL)
		printf(GREEN"[DEBUG] 🐷 Full: ID %d, Meals %d"RESET"\n",
			philo->id, meals);
	pthread_mutex_unlock(&philo->write_mutex);
}
