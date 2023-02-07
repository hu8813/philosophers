/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:58:36 by huaydin           #+#    #+#             */
/*   Updated: 2023/02/07 20:13:47 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->is_dead != 0 || philo->meals == philo->data->meals_to_eat)
	{
		philo->done = 1;
		pthread_mutex_unlock(&philo->data->m_dead);
		return (0);
	}
	if (ft_gettime() - philo->time_last_meal >= philo->data->time_to_die
		&& philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		ft_log(philo, "died");
		pthread_mutex_lock(&philo->data->m_dead);
		philo->data->is_dead = 1;
		philo->done = 1;
		pthread_mutex_unlock(&philo->data->m_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->meals != philo->data->meals_to_eat && !philo->done)
	{
		pthread_mutex_lock(&philo->data->m_dead);
		if (!philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->m_dead);
			if (!ft_eating(philo))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->m_dead);
			return (NULL);
		}
	}
	return (NULL);
}
