/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:34:51 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/12 12:50:29 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* 
Functions to handle errors, print error messages
 and clear data
 */

void	ft_free(t_data *data)
{
	if (data->data_thread)
		free(data->data_thread);
}

void	ft_clear(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->lock);
	ft_free(data);
}

int	ft_error(char *str, t_data *data)
{
	(void) data;
	printf("%s\n", str);
	if (data)
		ft_clear(data);
	return (1);
}
