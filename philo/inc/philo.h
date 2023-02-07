/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:26:58 by huaydin           #+#    #+#             */
/*   Updated: 2023/02/07 21:27:01 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_nbr;
	int				left_fork;
	int				right_fork;
	int				meals;
	int				done;
	long long		time_last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_dead;
	int				nbr_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long long		start_time;
	int				meals_to_eat;
	int				*forks;
	int				is_dead;
}					t_data;

int					ft_atol(const char *nptr);

int					ft_usleep(unsigned int time_to_delay, t_philo *philo);
long long			ft_gettime(void);
void				ft_free_destroy(t_data *data);
void				ft_log(t_philo *philo, char *state);

int					ft_init(t_data *data);

int					ft_eating(t_philo *philo);
int					ft_is_alive(t_philo *philo);
void				*ft_routine(void *arg);

#endif
