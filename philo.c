/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:07:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/10 19:56:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_params(char *argv[])
{
	if (!is_valid_number(argv[1]) || ft_atoi(argv[1]) <= 0)
		return (write(2,
				"Invalid number of philosophers.\n", 32), ERROR);
	if (!is_valid_number(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (write(2,
				"Invalid time to die.\n", 21), ERROR);
	if (!is_valid_number(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (write(2,
				"Invalid time to eat.\n", 21), ERROR);
	if (!is_valid_number(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (write(2,
				"Invalid time to sleep.\n", 23), ERROR);
	if (argv[5])
	{
		if (!is_valid_number(argv[5]) || ft_atoi(argv[5]) <= 0)
			return (write(2,
					"Invalid number of meals.\n", 25), ERROR);
	}
	return (SUCCESS);
}

void	init_params(t_simulation *sim, char *argv[])
{
	sim->start_time = now_in_ms();
	sim->n_philos = ft_atoi(argv[N_PHILOS]);
	sim->params.time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	sim->params.time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	sim->params.time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argv[MEALS_TO_EAT])
		sim->params.meals_to_eat = ft_atoi(argv[MEALS_TO_EAT]);
	else
		sim->params.meals_to_eat = -1;
}

int	init_philosophers(t_simulation *sim)
{
	size_t	i;

	sim->philos = (t_philo *) malloc(sizeof(t_philo) * sim->n_philos);
	if (!sim->philos)
		return (ERROR);
	i = 0;
	while (i < sim->n_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].is_alive = TRUE;
		sim->philos[i].last_meal_time = sim->start_time;
		sim->philos[i].params = &sim->params;
		sim->philos[i].mutex = &sim->mutex;
		i++;
	}
	return (SUCCESS);
}

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	while (philo->is_alive == TRUE)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (0);
}

void	init_threads(t_simulation *sim)
{
	size_t	i;
	int		tstatus;

	sim->threads = (pthread_t *) malloc(sim->n_philos * sizeof(pthread_t));
	if (!sim->threads)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < sim->n_philos)
	{
		tstatus = pthread_create(&sim->threads[i],
				NULL, philo_routine, (void *) &sim->philos[i]);
		if (tstatus != 0)
			exit(EXIT_FAILURE);
		tstatus = pthread_detach(sim->threads[i]);
		if (tstatus != 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	main_loop(t_simulation *sim)
{
	size_t	i;

	sim->running = TRUE;
	while (sim->running == TRUE)
	{
		i = 0;
		while (i < sim->n_philos)
		{
			if (sim->philos[i].is_alive == FALSE)
			{
				sim->running = FALSE;
				break ;
			}
			if (i == sim->n_philos - 1)
				i = 0;
			else
				i++;
		}
	}
}

void	clear_program(t_simulation *sim)
{
	free(sim->threads);
	free(sim->philos);
}

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	if (argc < ARG_MIN_COUNT || argc > ARG_MAX_COUNT)
		exit(EXIT_FAILURE);
	if (check_params(argv) != SUCCESS)
		exit(EXIT_FAILURE);
	init_params(&sim, argv);
	if (init_philosophers(&sim) != 0)
		exit(EXIT_FAILURE);
	pthread_mutex_init(&sim.mutex, NULL);
	init_threads(&sim);
	main_loop(&sim);
	pthread_mutex_destroy(&sim.mutex);
	clear_program(&sim);
	return (0);
}
