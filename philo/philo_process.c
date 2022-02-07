/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:41:59 by lubov             #+#    #+#             */
/*   Updated: 2022/02/07 23:22:03 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks_2(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->args->lock_pr);
	printf("%ld %u has taken a fork\n", \
		get_time() - philo->args->start, philo->philo_id);
	pthread_mutex_unlock(&philo->args->lock_pr);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->args->lock_pr);
	printf("%ld %u has taken a fork\n", \
		get_time() - philo->args->start, philo->philo_id);
	pthread_mutex_unlock(&philo->args->lock_pr);
}

void	get_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->args->lock_pr);
		printf("%ld %u has taken a fork\n", \
			get_time() - philo->args->start, philo->philo_id);
		pthread_mutex_unlock(&philo->args->lock_pr);
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&philo->args->lock_pr);
		printf("%ld %u has taken a fork\n", \
			get_time() - philo->args->start, philo->philo_id);
		pthread_mutex_unlock(&philo->args->lock_pr);
	}
	else
		get_forks_2(philo);
}

int	is_die(t_philo *philo)
{
	if (philo->die == 1)
		return (1);
	else if (philo->args->number_eat != -1 \
		&& philo->f_eat >= philo->args->number_eat)
		return (1);
	return (0);
}

void	*philo_process(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!(is_die(philo)))
	{
		get_forks(philo);
		eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}

void	init_thread(t_arg *args)
{
	int	i;

	i = 0;
	args->start = get_time();
	while (i < args->number_of_philo)
	{
		if (pthread_create(&(args->thread_philo[i]), \
			NULL, &philo_process, &args->data_philos[i]))
		{
			printf("ERROR thread create");
			exit(0);
		}
		i++;
		usleep(50);
	}
	check_philo(args);
}
