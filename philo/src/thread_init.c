/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:58:55 by huaydin           #+#    #+#             */
/*   Updated: 2023/02/07 20:06:30 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	alloc_mem(t_data *data)
{
	data->philo = malloc(sizeof * data->philo * data->nbr_philos);
	data->m_forks = malloc(sizeof * data->m_forks * data->nbr_philos);
	data->forks = malloc(sizeof * data->forks * data->nbr_philos);
	if (!data->philo || !data->m_forks || !data->forks)
	{
		printf("Error: Allocation failed\n");
		return (0);
	}
	return (1);
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
		{
			printf("Error: failed initializing one of the mutexes\n");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->m_write, NULL) != 0
		|| pthread_mutex_init(&data->m_dead, NULL) != 0)
	{
		printf("Error: failed initializing one of the mutexes\n");
		return (0);
	}
	return (1);
}

static void	init_philo_data(t_philo *philo, int i)
{
	philo->philo_id = i + 1;
	philo->meals = 0;
	philo->done = 0;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % philo->data->nbr_philos;
	philo->data->forks[i] = 0;
	philo->time_last_meal = philo->data->start_time;
}

static int	create_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(&data->philo[i].thread_nbr, NULL,
			ft_routine, (void *)&data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philo[i].thread_nbr, NULL) != 0)
		{
			printf("Error while joining the threads\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_init(t_data *data)
{
	int	i;

	i = 0;
	data->is_dead = 0;
	alloc_mem(data);
	if (!init_mutex(data))
		return (0);
	while (i < data->nbr_philos)
	{
		data->philo[i].data = data;
		init_philo_data(&data->philo[i], i);
		i++;
	}
	if (!create_threads(data))
		return (0);
	return (1);
}
