/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:27:18 by lubov             #+#    #+#             */
/*   Updated: 2022/02/08 01:33:41 by lubov            ###   ########.fr       */
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
			printf("Invalid input arguments(should only be numbers)");
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
	args->die = 0;
	return (0);
}

void	ft_philo(t_arg *args)
{
	int	i;

	i = 0;
	args->start = get_time();
	while (i < args->number_of_philo)
	{
		args->data_philos[i].pid = fork();
		if (args->data_philos[i].pid < 0)
			exit(1);
		if (args->data_philos[i].pid == 0)
		{
			if (pthread_create(&args->data_philos[i].check, \
				NULL, &check, &args->data_philos[i]))
				exit(1);
			philo_process(&(args->data_philos[i]), args);
			break ;
		}
		i++;
	}
	free_all(args, args->data_philos);
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
	ft_philo(&args);
}
