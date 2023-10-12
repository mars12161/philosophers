/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:43:34 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/12 12:53:03 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	retval;

	i = 0;
	neg = 1;
	retval = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = neg * (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			retval = (retval * 10) + (str[i] - '0');
		i++;
	}
	return (retval * neg);
}

void	print_status(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&(philo->data->printing));
	time = current_time() - philo->data->start_time;
	if (ft_strcmp("has died", msg) == 0 && philo->data->done == 0)
	{
		printf("%llu %d %s\n", time, philo->id, msg);
		philo->data->done = 1;
	}
	if (!philo->data->done)
		printf("%llu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->printing);
}

int	allocate(t_data *data)
{
	data->data_thread = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->data_thread)
		return (ft_error("malloc error", data));
	return (0);
}
