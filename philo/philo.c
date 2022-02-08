/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:43:47 by lubov             #+#    #+#             */
/*   Updated: 2022/02/03 22:43:47 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input_data(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of input arguments");
		return (1);
	}
	while (argv[i])
	{
		if (!(ft_isnumb(argv[i]) && ft_atoi(argv[i])))
		{
			printf("Invalid input arguments(should only be pos numbers)");
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_input_args(t_arg *args, int argc, char **argv)
{
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		args->number_eat = ft_atoi(argv[5]);
		if (args->number_eat < 1)
			return (1);
	}
	else
		args->number_eat = -1;
	if (args->number_of_philo < 1 || args->time_to_die < 1 \
		|| args->time_to_eat < 1 || args->time_to_sleep < 1)
		return (1);
	return (0);
}

int	check_live(t_philo *philo, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (philo[i].die == 1)
			return (0);
		else if (philo[i].args->number_eat != -1 \
			&& philo->f_eat >= philo[i].args->number_eat)
			return (0);
		i++;
	}
	return (1);
}

void	check_philo(t_arg *args)
{
	t_philo	*philo;
	long	time;
	int		i;

	philo = args->data_philos;
	while (check_live(philo, args->number_of_philo))
	{
		i = 0;
		while (i < args->number_of_philo
			&& check_live(philo, args->number_of_philo))
		{
			time = get_time() - philo[i].last_eat;
			if (time > args->time_to_die)
			{
				pthread_mutex_lock(&args->lock_pr);
				philo[i].die = 1;
				printf("%ld\t%d   is DIED\n", get_time()
					- args->start, philo[i].philo_id);
				free_all(args, 1);
				exit(0);
			}
			i++;
		}
	}
	free_all(args, 0);
}

int	main(int argc, char **argv)
{
	t_arg	args;

	if (check_input_data(argc, argv))
		return (1);
	if (init_input_args(&args, argc, argv))
	{
		printf("ERROR input arguments");
		return (1);
	}
	ft_malloc(&args);
	init_philo(&args);
	init_thread(&args);
}
