/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:12:21 by lubov             #+#    #+#             */
/*   Updated: 2022/02/07 23:19:42 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(int i, int l, int r, t_arg *args)
{
	args->data_philos[i].l_fork = &args->forks[l];
	args->data_philos[i].r_fork = &args->forks[r];
}

void	next_init_philo(t_arg *args, int i)
{
	while (i < args->number_of_philo)
	{
		args->data_philos[i].philo_id = i + 1;
		args->data_philos[i].die = 0;
		args->data_philos[i].last_eat = get_time();
		args->data_philos[i].f_eat = 0;
		args->data_philos[i].args = args;
		if (args->number_of_philo == 1)
			init_forks(i, i, i, args);
		else
		{
			if (i == 0 || i == (args->number_of_philo - 1))
			{
				if (i == 0)
					init_forks(i, (i - 1), i, args);
				init_forks(i, i, 0, args);
			}
			init_forks(i, i, (i + 1), args);
		}
		i++;
	}
}

void	init_philo(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL))
		{
			printf("ERROR mutex init");
			exit(1);
		}
		i++;
	}
	i = 0;
	next_init_philo(args, i);
}
