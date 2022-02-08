/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:28:53 by lubov             #+#    #+#             */
/*   Updated: 2022/02/08 19:41:00 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_end(t_arg *args, t_philo *philo)
{
	sem_wait(args->lock_pr);
	args->die = 1;
	printf("%ld\t%u\tis DIED\n", \
	get_time() - args->start, philo->philo_id);
	sem_post(args->end);
	exit(1);
}

void	*check(void *data)
{
	t_philo		*philo;
	t_arg		*args;
	long		time;

	philo = (t_philo *)data;
	args = philo->args;
	while (args->die == 0)
	{
		sem_wait(args->block_eat);
		time = get_time() - philo->last_eat;
		if (time > args->time_to_die)
			ft_end(args, philo);
		sem_post(args->block_eat);
		if (philo->f_eat >= philo->args->number_eat \
			&& philo->args->number_eat != -1)
			break ;
	}
	exit(1);
	return (NULL);
}

void	init_philo(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philo)
	{
		args->data_philos[i].philo_id = i + 1;
		args->data_philos[i].args = args;
		args->data_philos[i].last_eat = get_time();
		args->data_philos[i].f_eat = 0;
		i++;
	}
}
