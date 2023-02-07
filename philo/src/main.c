/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:59:05 by huaydin           #+#    #+#             */
/*   Updated: 2023/02/07 20:25:33 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_fill_struct(char **argv, t_data *data)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atol(argv[5]);
	else
		data->meals_to_eat = -1;
	data->start_time = ft_gettime();
	if (data->nbr_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	return (1);
}

static void	check_if_all_ate_x_times(t_data data)
{
	int	i;

	i = 0;
	if (data.meals_to_eat == -1)
		return ;
	while (i < data.nbr_philos)
	{
		if (data.philo[i].done == 0 || data.philo[i].meals != data.meals_to_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&data.philo->data->m_write);
	printf("%lld all have eaten %d times\n", ft_gettime()
		- data.start_time, data.meals_to_eat);
	pthread_mutex_unlock(&data.philo->data->m_write);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!ft_fill_struct(argv, &data))
			return (1);
		if (data.nbr_philos == 1)
		{
			printf("0 1 has taken a fork\n");
			usleep(data.time_to_die);
			printf("%d 1 died\n", ft_atol(argv[2]));
			return (0);
		}
		if (!ft_init(&data))
			return (1);
		check_if_all_ate_x_times(data);
		ft_free_destroy(&data);
	}
	else
	{
		printf("Usage:\n./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\nlast arg optional\n");
		return (1);
	}
	return (0);
}
