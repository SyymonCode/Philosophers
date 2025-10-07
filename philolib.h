/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:53:38 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/17 17:09:47 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				philo_count;
	int				someone_died;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	done_mutex;
	pthread_mutex_t	print_mutex;
	long			start_time;
	int				done_eating;
}					t_data;

typedef struct s_philo
{
	int				philo;
	int				ttd;
	int				tte;
	int				tts;
	int				number_eat;
	int				times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_mutex;
	long			last_meal;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

void	init_forks(int count, t_philo *philo, pthread_mutex_t *forks);
void	declare_philo(int count, t_philo *philo);
int		init_philo(t_philo **philo, \
	pthread_mutex_t **forks, t_data *data, char *argv[]);
int		not_ft_atoi(const char *nptr);
void	*routine(void *arg);
void	*check_death(void *arg);
int		get_death(t_data *data);
long	get_time_ms(void);
void	precise_usleep(long ms);
int		even_fork(t_philo *philo);
int		odd_fork(t_philo *philo);
void	print_muted(char *message, t_philo *philo);

#endif
