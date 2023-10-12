/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:55:48 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/01 11:44:16 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*meal_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (philo->data->done == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->all_ate >= philo->data->num_philos)
			philo->data->done = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*ate_check(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (philo->data->done == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (current_time() >= philo->time_to_die && philo->eating == 0)
			print_status(philo, "has died");
		if (philo->has_eaten == philo->data->num_must_eat)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->all_ate++;
			philo->has_eaten++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->time_to_die = philo->data->time_to_die + current_time();
	if (pthread_create(&philo->philo_thread, NULL, &ate_check, (void *)philo))
		return ((void *)1);
	while (philo->data->done == 0)
	{
		philo_eating(philo);
		print_status(philo, "is thinking");
	}
	if (pthread_join(philo->philo_thread, NULL))
		return ((void *)1);
	return ((void *)0);
}
