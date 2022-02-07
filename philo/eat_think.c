/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:04:38 by lubov             #+#    #+#             */
/*   Updated: 2022/02/07 23:17:38 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->args->lock_pr);
	printf("%ld %u is eating\n", get_time() - philo->args->start, \
		philo->philo_id);
	philo->f_eat++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->args->lock_pr);
	time = get_time();
	while (get_time() - time < philo->args->time_to_eat)
		usleep(500);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->args->lock_pr);
	printf("%ld %u is sleeping\n", get_time() - philo->args->start, \
		philo->philo_id);
	pthread_mutex_unlock(&philo->args->lock_pr);
	time = get_time();
	while (get_time() - time < philo->args->time_to_sleep)
		usleep(500);
	pthread_mutex_lock(&philo->args->lock_pr);
	printf("%ld %u is thinking\n", get_time() - philo->args->start, \
		philo->philo_id);
	pthread_mutex_unlock(&philo->args->lock_pr);
	usleep(100);
}

void	free_all_2(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->lock_pr);
	free(args->forks);
	free(args->data_philos);
	free(args->thread_philo);
}

void	free_all(t_arg *args, int type)
{
	int	i;

	i = 0;
	if (type == 1)
	{
		while (i < args->number_of_philo)
		{
			pthread_detach(args->thread_philo[i]);
			i++;
		}		
	}
	else
	{
		while (i < args->number_of_philo)
		{
			pthread_join(args->thread_philo[i], NULL);
			i++;
		}
	}
	free_all_2(args);
}

void	ft_malloc(t_arg *args)
{
	args->data_philos = malloc((sizeof(t_philo)) * args->number_of_philo);
	args->thread_philo = malloc(sizeof(pthread_t) * args->number_of_philo);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philo);
	if (!args->data_philos || !args->thread_philo || !args->forks)
	{
		printf("ERROR malloc");
		exit(1);
	}
	if (pthread_mutex_init(&args->lock_pr, NULL))
	{
		printf("ERROR mutex init");
		exit(1);
	}
}
