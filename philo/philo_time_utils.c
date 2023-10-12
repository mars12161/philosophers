/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:44:52 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/12 16:38:36 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ft_error("gettimeofday() failed\n", NULL));
	return ((time.tv_sec * (long long)1000) + (time.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	long long	start;

	start = current_time();
	while ((current_time() - start) < time)
		usleep(time / 10);
	return (0);
}
