/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:32:19 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 16:46:19 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static int	error_checker(char *argv[], int argc)
{
	if (not_ft_atoi(argv[1]) <= 0 || not_ft_atoi(argv[2]) <= 0
		|| not_ft_atoi(argv[3]) <= 0 || not_ft_atoi(argv[4]) <= 0)
	{
		printf("Arguments must be positive\n");
		return (0);
	}
	if (argc == 6 && not_ft_atoi(argv[5]) <= 0)
	{
		printf("Optional argument must be positive\n");
		return (0);
	}
	return (1);
}

static int	validate_arguments(int argc, char *argv[])
{
	if (argc < 5 || argc > 6 || !error_checker(argv, argc))
	{
		printf("Argument error\n");
		return (0);
	}
	return (1);
}

static void	initialize_data(t_data *data, char *argv[])
{
	data->philo_count = not_ft_atoi(argv[1]);
	data->someone_died = 0;
	data->start_time = get_time_ms();
	data->done_eating = 0;
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->done_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

static void	cleanup_resources(t_philo *philo, \
	pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->done_mutex);
	free(philo);
	free(forks);
}

int	main(int argc, char *argv[])
{
	t_philo			*philo;
	t_data			data;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	int				i;

	if (!validate_arguments(argc, argv))
		return (1);
	initialize_data(&data, argv);
	if (!init_philo(&philo, &forks, &data, argv))
		return (1);
	init_forks(data.philo_count, philo, forks);
	declare_philo(data.philo_count, philo);
	pthread_create(&monitor, NULL, check_death, (void *)philo);
	i = 0;
	while (i < data.philo_count)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(monitor, NULL);
	cleanup_resources(philo, forks, &data);
	return (0);
}
