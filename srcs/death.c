/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:46:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 17:32:54 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static int	skip_philo(t_philo *philo, int i)
{
	int	skip;

	pthread_mutex_lock(&philo[i].philo_mutex);
	skip = (philo[i].times_eaten == philo[i].number_eat);
	pthread_mutex_unlock(&philo[i].philo_mutex);
	return (skip);
}

int	get_death(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->death_mutex);
	res = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (res);
}

static int	has_died(t_philo *philo, t_data *data, int i)
{
	int	died;

	died = 0;
	pthread_mutex_lock(&philo[i].philo_mutex);
	if ((get_time_ms() - philo[i].last_meal) > philo[i].ttd)
	{
		died = 1;
	}
	pthread_mutex_unlock(&philo[i].philo_mutex);
	if (died)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = 1;
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has died\n", \
			get_time_ms() - philo->data->start_time, philo[i].philo + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

static int	check_done_eating(t_data *data)
{
	int	done;

	pthread_mutex_lock(&data->done_mutex);
	done = (data->done_eating == data->philo_count);
	pthread_mutex_unlock(&data->done_mutex);
	return (done);
}

void	*check_death(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)arg;
	data = philo[0].data;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (get_death(data))
				return (NULL);
			if (skip_philo(philo, i) || has_died(philo, data, i))
			{
				return (NULL);
			}
			i++;
		}
		if (check_done_eating(data))
			return (NULL);
		precise_usleep(10);
	}
}
