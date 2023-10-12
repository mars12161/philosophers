/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:42:46 by mschaub           #+#    #+#             */
/*   Updated: 2023/04/24 15:39:59 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&(data->forks[i]), NULL);
	i = 0;
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->num_philos - 1];
	i = 1;
	while (i < data->num_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].has_eaten = 0;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].eating = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->num_philos = (int) ft_atoi(argv[1]);
	data->time_to_die = (long long) ft_atoi(argv[2]);
	data->time_to_eat = (long long) ft_atoi(argv[3]);
	data->time_to_sleep = (long long) ft_atoi(argv[4]);
	data->done = 0;
	data->all_ate = 0;
	if (data->num_philos <= 0 || data->num_philos > 250)
		return (ft_error("wrong number of philos", NULL));
	if (argv[5])
	{
		data->num_must_eat = (int) ft_atoi(argv[5]);
		if (data->num_must_eat <= 0)
			return (1);
	}
	else
		data->num_must_eat = -1;
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init_thread(t_data *data)
{
	int			i;
	pthread_t	thread;

	i = -1;
	data->start_time = current_time();
	if (data->num_must_eat > 0)
	{
		if (pthread_create(&thread, NULL, &meal_checker, &data->philos[0]))
			return (ft_error("error creating thread", data));
	}
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->data_thread[i], NULL,
				&philo_routine, &data->philos[i]))
			return (ft_error("error creating thread", data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->data_thread[i], NULL))
			return (ft_error("error joining threads", data));
	}
	return (0);
}

int	init_all(t_data *data, char **argv)
{
	if (init_data(data, argv))
		return (1);
	if (allocate(data))
		return (1);
	if (init_mutex(data))
		return (1);
	init_philos(data);
	return (0);
}
