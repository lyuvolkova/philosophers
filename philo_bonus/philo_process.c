/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 00:23:00 by lubov             #+#    #+#             */
/*   Updated: 2022/02/08 19:38:35 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_print(t_philo *philo)
{
	if (philo->f_eat >= philo->args->number_eat \
		&& philo->args->number_eat != -1)
	{
		sem_post(philo->args->end);
		return (1);
	}
	return (0);
}

void	get_forks(t_philo *philo, t_arg *args)
{
	sem_wait(args->forks);
	sem_wait(args->lock_pr);
	printf("%ld\t%u\thas taken a fork\n", \
		get_time() - philo->args->start, philo->philo_id);
	if (!check_print(philo))
		sem_post(args->lock_pr);
	sem_wait(args->forks);
	sem_wait(args->lock_pr);
	printf("%ld\t%u\thas taken a fork\n", \
		get_time() - philo->args->start, philo->philo_id);
	if (!check_print(philo))
		sem_post(args->lock_pr);
}

void	philo_process(t_philo *philo, t_arg *args)
{
	while (args->die == 0)
	{
		get_forks(philo, args);
		eating(philo, args);
		sleep_think(philo, args);
	}
	exit(1);
}
