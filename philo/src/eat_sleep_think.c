/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:59:16 by huaydin           #+#    #+#             */
/*   Updated: 2023/02/07 20:04:01 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_sleep(t_philo *philo)
{
	if (!ft_is_alive(philo))
		return (0);
	ft_log(philo, "is sleeping");
	if (!ft_usleep(philo->data->time_to_sleep, philo))
		return (0);
	if (!ft_is_alive(philo))
		return (0);
	ft_log(philo, "is thinking");
	ft_usleep(1, philo);
	return (1);
}

int	ft_eat(t_philo *philo, int lock_order)
{
	philo->data->forks[philo->right_fork] = philo->philo_id;
	philo->data->forks[philo->left_fork] = philo->philo_id;
	if (lock_order == 0)
	{
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
	}
	else if (lock_order == 1)
	{
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
	}
	if (!ft_is_alive(philo))
		return (0);
	ft_log(philo, "has taken a fork");
	ft_log(philo, "has taken a fork");
	ft_log(philo, "is eating");
	philo->time_last_meal = ft_gettime();
	if (!ft_usleep(philo->data->time_to_eat, philo))
		return (0);
	philo->meals++;
	return (1);
}

static void	ft_drop_forks(t_philo *philo, int lock_order)
{
	if (lock_order == 0)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
		philo->data->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
		philo->data->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
	}
	else if (lock_order == 1)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
		philo->data->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
		philo->data->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
	}
}

static void	lock_unlock_forks(t_philo *philo, int flag, int lock_order)
{
	if (flag == 1 && lock_order == 0)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
	}	
	else if (flag == 1 && lock_order == 1)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
	}
	else
	{
		if (lock_order == 0)
		{
			pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
		}
	}
}

int	ft_eating(t_philo *philo)
{
	if (!ft_is_alive(philo))
		return (0);
	lock_unlock_forks(philo, 1, philo->philo_id % 2);
	if (philo->data->forks[philo->right_fork] == 0
		&& philo->data->forks[philo->left_fork] == 0)
	{
		if (!ft_eat(philo, philo->philo_id % 2))
			return (0);
		ft_drop_forks(philo, philo->philo_id % 2);
		if (!ft_sleep(philo))
			return (0);
		return (1);
	}
	else
	{
		lock_unlock_forks(philo, 0, philo->philo_id % 2);
		if (!ft_is_alive(philo))
			return (0);
	}
	return (1);
}
