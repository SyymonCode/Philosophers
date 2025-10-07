/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:13:53 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 17:31:49 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	even_fork(t_philo *philo)
{
	precise_usleep(1);
	pthread_mutex_lock(philo->left_fork);
	if (get_death(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_muted("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	if (get_death(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_muted("has taken a fork", philo);
	return (0);
}

int	odd_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (get_death(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_muted("has taken a fork", philo);
	pthread_mutex_lock(philo->left_fork);
	if (get_death(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_muted("has taken a fork", philo);
	return (0);
}
