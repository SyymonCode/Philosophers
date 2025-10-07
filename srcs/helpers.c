/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:57:01 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 17:22:41 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	precise_usleep(long ms)
{
	long			start;
	long			now;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&tv, NULL);
		now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (now - start >= ms)
			break ;
		usleep(100);
	}
}

void	print_muted(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s,\n", get_time_ms() - \
	philo->data->start_time, philo->philo + 1, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
