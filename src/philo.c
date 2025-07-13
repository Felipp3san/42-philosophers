/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:07:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 22:53:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

// TODO: Full philosopher
void	*philo_routine(void *philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) philosopher;
	table = (t_table *) philo->table;
	while (!simulation_finished(table))
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}

// TODO: Lone philosopher
// TODO: Sync thread to start simultaneous
// TODO: Join all threads
void	init_threads(t_table *table)
{
	t_philo	*philo;
	ssize_t	i;
	int		status;

	i = -1;
	while (++i < table->n_philos)
	{
		philo = &table->philos[i];
		status = pthread_create(&philo->thread,
				NULL, philo_routine, (void *) philo);
		if (status != 0)
		{
			free_table(table);
			exit_error("Failed to create thread");
		}
	}
}

void	free_table(t_table *table)
{
	clean_table(table);
	clean_forks(table);
	clean_philosophers(table);
}

static void	check_params(char *argv[])
{
	if (!is_valid_number(argv[1]) || ft_atoi(argv[1]) <= 0)
		exit_error("Invalid number of philosophers");
	if (!is_valid_number(argv[2]) || ft_atoi(argv[2]) <= 0)
		exit_error("Invalid time to die");
	if (!is_valid_number(argv[3]) || ft_atoi(argv[3]) <= 0)
		exit_error("Invalid time to eat");
	if (!is_valid_number(argv[4]) || ft_atoi(argv[4]) <= 0)
		exit_error("Invalid time to sleep");
	if (argv[5])
	{
		if (!is_valid_number(argv[5]) || ft_atoi(argv[5]) <= 0)
			exit_error("Invalid number of meals");
	}
}

int	main(int argc, char *argv[])
{
	t_table		table;
	pthread_t	monitor;
	ssize_t		i;

	if (argc < ARG_MIN_COUNT || argc > ARG_MAX_COUNT)
		exit_error("Invalid number of parameters");
	check_params(argv);
	init_data(&table, argv);
	init_threads(&table);
	init_monitor(&monitor, &table);
	i = -1;
	while (++i < table.n_philos)
		pthread_join(table.philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	free_table(&table);
	return (EXIT_SUCCESS);
}
