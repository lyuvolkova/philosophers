/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:39:59 by lubov             #+#    #+#             */
/*   Updated: 2022/02/08 01:02:56 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all_2(t_arg *args)
{
	free(args->data_philos);
	sem_unlink("/forks");
	sem_close(args->forks);
	sem_unlink("/logs");
	sem_close(args->lock_pr);
	sem_unlink("/end");
	sem_close(args->end);
	sem_unlink("/ttd");
	sem_close(args->block_eat);
}

int	parent(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->number_of_philo)
	{
		if (philo[i].pid == 0)
			return (0);
		i++;
	}	
	return (1);
}

void	free_all(t_arg *args, t_philo *philo)
{
	int	i;

	sem_wait(args->end);
	if (parent(philo))
	{
		i = 0;
		while (i < args->number_of_philo)
		{
			kill(philo[i].pid, SIGTERM);
			i++;
		}
		i = 0;
		while (i < args->number_of_philo)
		{
			waitpid(philo[i].pid, NULL, 0);
			i++;
		}
	}
	free_all_2(args);
}

void	sleep_think(t_philo *philo, t_arg *args)
{
	long long	time;

	sem_wait(args->lock_pr);
	printf("%ld %u is sleeping\n", get_time() - philo->args->start, \
		philo->philo_id + 1);
	if (!check_print(philo))
		sem_post(args->lock_pr);
	time = get_time();
	while (get_time() - time < philo->args->time_to_sleep)
		usleep(500);
	sem_wait(args->lock_pr);
	printf("%ld %u is thinking\n", get_time() - philo->args->start, \
		philo->philo_id);
	if (!check_print(philo))
		sem_post(args->lock_pr);
	usleep(100);
}

void	eating(t_philo *philo, t_arg *args)
{
	long	time;

	sem_wait(args->lock_pr);
	printf("%ld %u is eating\n", get_time() - philo->args->start, \
		philo->philo_id);
	sem_wait(args->block_eat);
	philo->f_eat++;
	philo->last_eat = get_time();
	if (!check_print(philo))
		sem_post(args->lock_pr);
	sem_post(args->block_eat);
	time = get_time();
	while (get_time() - time < philo->args->time_to_eat)
		usleep(500);
	sem_post(args->forks);
	sem_post(args->forks);
}

void	ft_malloc(t_arg *args)
{
	args->data_philos = malloc((sizeof(t_philo)) * args->number_of_philo);
	if (!args->data_philos)
	{
		printf("ERROR malloc");
		exit(1);
	}
	sem_unlink("/forks");
	sem_unlink("/logs");
	sem_unlink("/end");
	sem_unlink("/ttd");
	args->forks = sem_open("/forks", O_CREAT | O_EXCL, \
		777, args->number_of_philo);
	args->lock_pr = sem_open("/logs", O_CREAT | O_EXCL, 777, 1);
	args->end = sem_open("/end", O_CREAT | O_EXCL, 777, 0);
	args->block_eat = sem_open("/ttd", O_CREAT | O_EXCL, 777, 1);
	if (args->forks <= 0 || args->lock_pr <= 0 || \
		args->end <= 0 || args->block_eat <= 0)
	{
		printf("ERROR semaphore");
		exit(1);
	}
}