/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:44:43 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/12 13:43:13 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo(t_data *data)
{
	data->start_time = current_time();
	philo_eating(data->philos);
	if (pthread_create(&data->data_thread[0], NULL,
			&ate_check, &data->philos[0]))
		return (ft_error("error creating thread", data));
	pthread_detach(data->data_thread[0]);
	while (data->done == 0)
		ft_usleep(1);
	ft_clear(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_input(argv))
		return (1);
	if (init_all(&data, argv))
		return (1);
	if (data.num_philos == 1)
		return (one_philo(&data));
	if (init_thread(&data))
		return (1);
	ft_clear(&data);
	return (0);
}
