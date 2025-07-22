/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:07:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:53:40 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	join_threads(t_table	*table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->death_monitor, NULL);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < ARG_MIN_COUNT || argc > ARG_MAX_COUNT)
		exit_error("Invalid number of parameters");
	check_params(argv);
	init_data(&table, argv);
	init_monitor(&table);
	init_threads(&table);
	join_threads(&table);
	free_table(&table);
	return (EXIT_SUCCESS);
}
