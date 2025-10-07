/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:58:42 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 17:11:18 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static	int	routine_actions(t_philo *philo)
{
	if (get_death(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_muted("is eating", philo);
	precise_usleep(philo->tte);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (get_death(philo->data))
		return (1);
	print_muted("is sleeping", philo);
	precise_usleep(philo->tts);
	if (get_death(philo->data))
		return (1);
	print_muted("is thinking", philo);
	return (0);
}

static int	fork_taking(t_philo *philo)
{
	if (philo->philo % 2 == 0)
	{
		if (even_fork(philo) == 1)
			return (1);
	}
	else
	{
		if (odd_fork(philo) == 1)
			return (1);
	}
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->philo_mutex);
	if (routine_actions(philo))
		return (1);
	return (0);
}

static int	philo_loop(t_philo *philo)
{
	int	te;

	while (!get_death(philo->data))
	{
		pthread_mutex_lock(&philo->philo_mutex);
		te = philo->times_eaten;
		pthread_mutex_unlock(&philo->philo_mutex);
		if (philo->number_eat != -1 && te >= philo->number_eat)
			return (1);
		if (fork_taking(philo))
			return (1);
	}
	return (0);
}

static void	mark_done_eating(t_philo *philo)
{
	int	te;

	if (philo->number_eat != -1)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		te = philo->times_eaten;
		pthread_mutex_unlock(&philo->philo_mutex);
		if (te == philo->number_eat)
		{
			pthread_mutex_lock(&philo->data->done_mutex);
			philo->data->done_eating++;
			pthread_mutex_unlock(&philo->data->done_mutex);
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_muted("has taken a fork", philo);
		precise_usleep(philo->ttd);
		return (pthread_mutex_unlock(philo->left_fork), NULL);
	}
	pthread_mutex_lock(&philo->philo_mutex);
	philo->times_eaten = 0;
	pthread_mutex_unlock(&philo->philo_mutex);
	philo_loop(philo);
	mark_done_eating(philo);
	return (NULL);
}
