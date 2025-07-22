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

void	write_status(t_philo *philo, t_state state)
{
	t_table	*table;
	t_ull	timestamp;

	table = philo->table;
	timestamp = now_in_ms() - table->times.start_time;
	pthread_mutex_lock(&philo->write_mutex);
	if (state == TAKEN_FORK && !simulation_finished(table))
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
