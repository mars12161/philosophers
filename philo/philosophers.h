/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:54:46 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/12 13:52:45 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int					id;
	int					has_eaten;
	int					eating;
	struct s_data		*data;
	long long			time_to_die;
	pthread_t			philo_thread;
	pthread_mutex_t		lock;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
}			t_philo;

typedef struct s_data
{
	int				num_philos;
	int				num_must_eat;
	int				done;
	int				all_ate;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	t_philo			philos[256];
	pthread_mutex_t	printing;
	pthread_mutex_t	forks[256];
	pthread_mutex_t	lock;
	pthread_t		*data_thread;
}	t_data;

/* Error messages */
void		ft_free(t_data *data);
void		ft_clear(t_data *data);
int			ft_error(char *str, t_data *data);
int			check_input(char **argv);

/* Time management */
long long	current_time(void);
int			ft_usleep(useconds_t time);

/* Utils */
int			ft_atoi(const char *str);
void		print_status(t_philo *philo, char *msg);
int			ft_strcmp(char *s1, char *s2);
int			allocate(t_data *data);
void		philo_eating(t_philo *philo);
void		philo_take_forks(t_philo *philo);
void		philo_drop_forks(t_philo *philo);

/* Init */
int			init_thread(t_data *data);
int			init_data(t_data *data, char **argv);
int			init_philos(t_data *data);
int			init_mutex(t_data *data);
int			init_all(t_data *data, char **argv);

/* Starting philo */
void		*meal_checker(void *arg);
void		*ate_check(void *arg);
void		*philo_routine(void *arg);
int			one_philo(t_data *data);

#endif
