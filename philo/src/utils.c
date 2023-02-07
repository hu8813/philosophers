/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:52:07 by huaydin           #+#    #+#             */
/*   Updated: 2023/02/07 18:36:54 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_log(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_write);
	if (!philo->done && !philo->data->is_dead
		&& philo->meals != philo->data->meals_to_eat)
	{	
		printf("%lld %d %s\n", (ft_gettime() - philo->data->start_time),
			philo->philo_id, state);
	}
	pthread_mutex_unlock(&philo->data->m_write);
	pthread_mutex_unlock(&philo->data->m_dead);
}

int	ft_usleep(unsigned int time_to_delay, t_philo *philo)
{
	long long	now;

	now = ft_gettime();
	if (!ft_is_alive(philo))
		return (0);
	while ((ft_gettime() - now) < ((long long)time_to_delay))
	{
		if (!ft_is_alive(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

long long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_free_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->m_write);
	pthread_mutex_destroy(&data->m_dead);
	free(data->m_forks);
	free(data->philo);
	free(data->forks);
}

int	ft_atol(const char *nptr)
{
	int			i;
	long		s;
	long long	res;

	res = 0;
	s = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	if ((!(nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != ' ' && nptr[i] != 0)
		|| (res * s) < -2147483648 || (res * s) > 2147483647 || s == -1)
		return (0);
	return ((int)(res * s));
}
