/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:20:13 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 17:39:30 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	declare_philo(int count, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			printf("Thread creation failed for philosopher %d\n", i);
			return ;
		}
		i++;
	}
}

int	init_philo(t_philo **philo, \
	pthread_mutex_t **forks, t_data *data, char *argv[])
{
	int	i;
	int	number_eat;

	*philo = malloc(sizeof(t_philo) * data->philo_count);
	*forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!*philo || !*forks)
		return (0);
	if (argv[5])
		number_eat = not_ft_atoi(argv[5]);
	else
		number_eat = -1;
	i = 0;
	while (i++ < data->philo_count)
	{
		pthread_mutex_init(&(*philo)[i - 1].philo_mutex, NULL);
		(*philo)[i - 1].philo = i - 1;
		(*philo)[i - 1].ttd = not_ft_atoi(argv[2]);
		(*philo)[i - 1].tte = not_ft_atoi(argv[3]);
		(*philo)[i - 1].tts = not_ft_atoi(argv[4]);
		(*philo)[i - 1].number_eat = number_eat;
		(*philo)[i - 1].last_meal = get_time_ms();
		(*philo)[i - 1].data = data;
		(*philo)[i - 1].times_eaten = 0;
	}
	return (1);
}

void	init_forks(int count, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < count)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % count];
		i++;
	}
}

int	not_ft_atoi(const char *nptr)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	if (nptr[i] < '0' || nptr[i] > '9')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		val = val * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	return (val);
}
